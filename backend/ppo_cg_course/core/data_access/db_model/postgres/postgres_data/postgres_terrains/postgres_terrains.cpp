#include "postgres_terrains.h"

TerrainProjectsPostgres::TerrainProjectsPostgres(std::shared_ptr<pqxx::connection> &conn_psql){
    __conn_psql = conn_psql;
    __define_count_terrain_projects();
}

void TerrainProjectsPostgres::__define_count_terrain_projects()
{
    pqxx::result response;
    std::string query;
    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT COUNT(*) FROM terrain_project.terrains.projects";
        response = worker.exec(query);
        __count_terrain_projs = std::stoi(response[0][0].c_str());
    }
    catch(std::exception const &e){
        std::cout << e.what() << '\n';
        return;
    }
}

void TerrainProjectsPostgres::set_terrain_params(std::string &project_name, dbTerrain_t &terrain_params){
    pqxx::work worker(*__conn_psql);
    std::string query = "UPDATE terrain_project.terrains.terrains SET ('" + \
                         std::to_string(terrain_params.width) + "', '" + \
                         std::to_string(terrain_params.height) + "', '" + \
                         std::to_string(terrain_params.scale) + "', '" + \
                         std::to_string(terrain_params.meta_config.octaves) + "', '" + \
                         std::to_string(terrain_params.meta_config.gain) + "', '" + \
                         std::to_string(terrain_params.meta_config.lacunarity) + "', '" + \
                         std::to_string(terrain_params.meta_config.seed) + "', '" + \
                         std::to_string(terrain_params.meta_config.frequency) + "', '" + \
                         std::to_string(terrain_params.rotate_angles.angle_x) + "', '" + \
                         std::to_string(terrain_params.rotate_angles.angle_y) + "', '" + \
                         std::to_string(terrain_params.rotate_angles.angle_z) + \
                         "WHERE terrain_project.terrains.terrains = " + project_name + "';'";
    worker.exec(query);
    worker.commit();
}

///Return all user terrain projects
int TerrainProjectsPostgres::get_terrain_projects(const int &user_id,
                                                  std::vector<dbTerrainProject_t> &dbTerProjs)
{
    std::string id_user = std::to_string(user_id);
    pqxx::work worker(*__conn_psql);
    pqxx::result response;
    int ret_code = SUCCESS;
    int count_ter_projs;
    std::string query;

    query = "SELECT ter_projs.id, ter_projs.name, ter_projs.last_edited \
                        FROM terrain_project.terrains.projects as ter_projs \
                        JOIN terrain_project.terrains.terrains_users as ter_user \
                             on ter_projs.id = ter_user.id_terrain \
                        JOIN terrain_project.users.info as info \
                             on info.id = ter_user.id_user where id_user = " + id_user + ";";
    try{
        response = worker.exec(query);

        if (response.empty()){
            ret_code = NOT_FOUND;
        }
        else{
            count_ter_projs = response.size();
            dbTerProjs.resize(count_ter_projs);
            for (int i = 0; i < count_ter_projs; ++i){
                dbTerProjs[i].id = response[i][0].as<int>();
                dbTerProjs[i].name = response[i][1].c_str();
                dbTerProjs[i].last_edit = response[i][2].c_str();
            }
        }
    }
    catch(std::exception &e){
        std::cerr << e.what();
        return BAD_REQUEST;
    }
    return ret_code;
}

int TerrainProjectsPostgres::get_count_terrain_projects(){
    return __count_terrain_projs;
}

int TerrainProjectsPostgres::add_new_terrain_project(const int &user_id, const std::string &terProjName)
{
    int new_ter_id = __count_terrain_projs + 1;
    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    pqxx::work worker(*__conn_psql);
    try{
        std::string query = "INSERT INTO terrain_project.terrains.terrains VALUES (" +
                            std::to_string(new_ter_id) + ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);";

        __count_terrain_projs++;

        worker.exec(query);

        query = "INSERT INTO terrain_project.terrains.projects VALUES (" +
                std::to_string(new_ter_id) + ", '" + terProjName + "', " + "'2022-01-01', " +
                std::to_string(new_ter_id) + ");";

        worker.exec(query);

        query = "INSERT INTO terrain_project.terrains.terrains_users VALUES (" +
                std::to_string(user_id) + ", " + std::to_string(new_ter_id) + ");";

        worker.exec(query);
        worker.commit();
        std::cerr << "success_created\n";
    }
    catch (std::exception &e){
        std::cerr << e.what();
        return BAD_REQUEST;
    }

    return SUCCESS_CREATED;
}

int TerrainProjectsPostgres::get_terrain_params(const int &user_id, const int &terId, dbTerrain_t &ter)
{
    pqxx::result response;
    std::string query;
    int ret_code = SUCCESS;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }
    else if (terId > __count_terrain_projs){
        return NOT_FOUND;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT ter.width, ter.height, ter.scale, ter.octaves, ter.gain, ter.lacunarity, \
                        ter.seed, ter.frequency, ter.angle_x, ter.angle_y, ter.angle_z \
                 FROM terrain_project.terrains.projects as proj\
                      JOIN terrain_project.terrains.terrains as ter on \
                           proj.id_terrain = ter.id \
                      JOIN terrain_project.terrains.terrains_users as ter_usr \
                           on ter_usr.id_terrain = proj.id_terrain \
                 WHERE ter_usr.id_user = " + std::to_string(user_id) + " AND proj.id_terrain = " +
                  std::to_string(terId) + ";";

        response = worker.exec(query);
        if (response.empty()){
            ret_code = NOT_FOUND;
        }
        else{
            ter.width = response[0][0].as<int>();
            ter.height = response[0][1].as<int>();
            ter.scale = response[0][2].as<double>();
            ter.meta_config.octaves = response[0][3].as<int>();
            ter.meta_config.gain = response[0][4].as<double>();
            ter.meta_config.lacunarity = response[0][5].as<double>();
            ter.meta_config.seed = response[0][6].as<int>();
            ter.meta_config.frequency = response[0][7].as<double>();
            ter.rotate_angles.angle_x = response[0][8].as<int>();
            ter.rotate_angles.angle_y = response[0][9].as<int>();
            ter.rotate_angles.angle_z = response[0][10].as<int>();
        }
    }
    catch(std::exception &e){
        std::cerr << e.what();
        return ret_code;
    }

    return ret_code;
}

int TerrainProjectsPostgres::delete_terrain_project(const int &userId, const int &terId)
{
    pqxx::result response;
    std::string query, ter_id;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try {
        ter_id = std::to_string(terId);
        pqxx::work worker(*__conn_psql);
        query = "DELETE \
                FROM terrain_project.terrains.terrains_users \
                WHERE id_user = " + std::to_string(userId) + " ;" +

                "DELETE \
                FROM terrain_project.terrains.projects \
                WHERE id = " + ter_id + " ;" +

                "DELETE \
                FROM terrain_project.terrains.terrains \
                WHERE id = " + ter_id + " ; ";

        response = worker.exec(query);
        worker.commit();

        std::cout << "Удаление проекта с ландшафтом выполнено успешно.\n";
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        return BAD_REQUEST;
    }

    return SUCCESS;
}

double TerrainProjectsPostgres::get_terrain_project_rating(const int &terId, double &dbRating)
{
    pqxx::result response;
    std::string query, ter_id;
    int ret_code = SUCCESS;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try{
        if (terId < 1 || terId > __count_terrain_projs){
            ret_code = NOT_FOUND;
        }
        else{
            ter_id = std::to_string(terId);
            pqxx::work worker(*__conn_psql);
            query = "SELECT rating\
                     FROM terrain_project.terrains.projects \
                     WHERE id = " + ter_id + " AND exhibited = true;";
            response = worker.exec(query);

            if (!response.empty()){
                dbRating = std::stoi(response[0][0].c_str());
            }
            else{
                ret_code = NOT_FOUND;
            }
        }
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
        return BAD_REQUEST;
    }

    return ret_code;
}

int TerrainProjectsPostgres::set_terrain_project_rating(const int &terId, const int &rating)
{
    pqxx::result response;
    std::string query, ter_id;
    double old_rating, new_rating;
    int n_rates, response_code;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try{
        pqxx::work worker(*__conn_psql);
        if (terId < 1 || terId > __count_terrain_projs){
            response_code = NOT_FOUND;
        }
        else{
            response_code = SUCCESS;
            ter_id = std::to_string(terId);
            query = "SELECT rating, n_rates\
                     FROM terrain_project.terrains.projects \
                     WHERE id = " + ter_id + " AND exhibited = true;";
            response = worker.exec(query);

            if (!response.empty()){
                old_rating = std::stod(response[0][0].c_str());
                n_rates = std::stoi(response[0][1].c_str());
                new_rating = (old_rating * n_rates + rating) / (n_rates + 1);
                n_rates++;
                query = "UPDATE terrain_project.terrains.projects \
                         SET rating=" + std::to_string(new_rating) + ", n_rates=" + std::to_string(n_rates) + "\
                         WHERE id= " + ter_id + ";";
                worker.exec(query);
                worker.commit();
            }
        }
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
        return BAD_REQUEST;
    }

    return response_code;
}
