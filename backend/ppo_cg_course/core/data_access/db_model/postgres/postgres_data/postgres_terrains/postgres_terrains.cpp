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
int TerrainProjectsPostgres::get_terrain_projects(const int &user_id, int &page,
                                                  std::vector<dbTerrainProject_t> &dbTerProjs)
{
    std::string id_user = std::to_string(user_id), pageCard = std::to_string(page);
    pqxx::work worker(*__conn_psql);
    pqxx::result response;
    int ret_code = SUCCESS;
    int count_ter_projs;
    std::string query;
    std::cerr << "get_terrain_projects\n";

    query = "SELECT ter_projs.name, ter_projs.last_edited \
                        FROM terrain_project.terrains.projects as ter_projs \
                        JOIN terrain_project.terrains.users_projs as ter_user \
                             on ter_projs.name = ter_user.proj_name \
                        JOIN terrain_project.users.info as info \
                             on info.id = ter_user.id_user where id_user = " + id_user +
                        " ORDER BY ter_projs.last_edited DESC, ter_projs.id_terrain DESC \
                        LIMIT 3 OFFSET "+ std::to_string((page-1)*3) + ";";
    try{
        response = worker.exec(query);
        std::cerr << "response.size: " << response.size() << "\n";

        if (response.empty()){
            ret_code = SUCCESS;
        }
        else{
            count_ter_projs = response.size();
            dbTerProjs.resize(count_ter_projs);
            for (int i = 0; i < count_ter_projs; ++i){
                dbTerProjs[i].name = response[i][0].c_str();
                dbTerProjs[i].last_edit = response[i][1].c_str();
            }
        }
    }
    catch(std::exception &e){
        std::cerr << e.what();
        return BAD_REQUEST;
    }
    std::cerr << "ret_code: " << ret_code << "\n";
    return ret_code;
}

int TerrainProjectsPostgres::get_terrain_project(const int userId, const std::string &projName,
                                                 dbTerrainProject_t &dbTerProj)
{
    std::string id_user = std::to_string(userId);
    pqxx::work worker(*__conn_psql);
    pqxx::result response;
    int ret_code = SUCCESS;
    std::string query;

    query = "SELECT name, last_edited, rating, n_rates, exhibited\
             FROM terrain_project.terrains.projects as ter_projs \
             JOIN terrain_project.terrains.users_projs as user_proj\
                  on ter_projs.name = user_proj.proj_name \
             WHERE ter_projs.name ='" + projName + "';";

    try{
        response = worker.exec(query);
        std::cerr << "response_size: " << response.size() << "\n";
        if (!response.size()){
            ret_code = NOT_FOUND;
        }
        else{
            dbTerProj.name = response[0][0].c_str();
            dbTerProj.last_edit = response[0][1].c_str();
            dbTerProj.rating = response[0][2].is_null() ? 0 : response[0][2].as<double>();
            dbTerProj.n_rates = response[0][3].is_null() ? 0 : response[0][3].as<int>();
            dbTerProj.exhibited = response[0][4].is_null() ? false : response[0][4].as<bool>();
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

int TerrainProjectsPostgres::set_terrain_params(
        const int &user_id, const std::string &projName, const dbTerrain_t &ter)
{
    pqxx::result response;
    std::string query;
    int success = SUCCESS;
    pqxx::work worker(*__conn_psql);
    std::cerr << "GET_TERRAIN_PARAMS\n";
    std::string id_terrain;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    query = "SELECT id_terrain \
             FROM terrain_project.terrains.users_projs \
             JOIN terrain_project.terrains.projects ON users_projs.proj_name = projects.name \
             WHERE users_projs.id_user = "+std::to_string(user_id)+" AND users_projs.proj_name = '"+projName+"';";
    try{
        response = worker.exec(query);
        if (!response[0][0].is_null()){
            id_terrain = response[0][0].c_str();
            std::cerr << "id_terrain: " << id_terrain << "\n";
            query = "UPDATE terrain_project.terrains.terrains SET \
                    width = "+std::to_string(ter.width)+
                    ",height= "+ std::to_string(ter.height)+","+
                    "scale="+std::to_string(ter.scale)+","+
                    "octaves="+std::to_string(ter.meta_config.octaves)+","+
                    "gain="+std::to_string(ter.meta_config.gain)+","+
                    "lacunarity="+std::to_string(ter.meta_config.lacunarity)+","+
                    "seed="+std::to_string(ter.meta_config.seed)+","+
                    "frequency="+std::to_string(ter.meta_config.frequency)+","+
                    "angle_x="+std::to_string(ter.rotate_angles.angle_x)+","+
                    "angle_y="+std::to_string(ter.rotate_angles.angle_y)+","+
                    "angle_z="+std::to_string(ter.rotate_angles.angle_z)+" "+
                    "WHERE id = " + id_terrain+ ";";
            worker.exec(query);
            worker.commit();
        }
        else{
            success = BAD_REQUEST;
        }
        std::cerr << "success: " << success << "\n";
    }
    catch (std::exception &e){
        std::cerr << e.what();
        return BAD_REQUEST;
    }

    return success;
}

int TerrainProjectsPostgres::add_new_terrain_project(const int &user_id, const std::string &terProjName)
{
    std::string query, newTerId;
    int success = SUCCESS_CREATED;
    pqxx::result response;
    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    pqxx::work worker(*__conn_psql);
    try{
        query = "SELECT COUNT(*) \
                 FROM terrain_project.terrains.users_projs \
                 WHERE proj_name='" + terProjName + "';";
        response = worker.exec(query);
        std::cerr << "response[0][0].as<int>(): " << response[0][0].as<int>() << "\n";
        if (response[0][0].as<int>() == 1){
            success = CONFLICT;
        }
        else{
            query = "SELECT MAX(id) from terrain_project.terrains.terrains;";
            response = worker.exec(query);

            std::cerr << "response[0][0].c_str(): " << response[0][0].c_str() << "\n";
            std::cerr << "response[0][0].c_str() is NULL: " << (response[0][0].is_null()) << "\n";
            newTerId = (response[0][0].is_null()) ? "1" : std::to_string(response[0][0].as<int>() + 1);

            std::cerr << "newTerId: " << newTerId << "\n";

            query = "INSERT INTO terrain_project.terrains.terrains VALUES (" +
                                newTerId + ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);";

            __count_terrain_projs++;

            worker.exec(query);

            query = "INSERT INTO terrain_project.terrains.projects VALUES ('"
                    + terProjName + "', " + "'today', null, null, null, " + newTerId + ");";

            worker.exec(query);

            query = "INSERT INTO terrain_project.terrains.users_projs VALUES (" +
                    std::to_string(user_id) + ", '" + terProjName + "');";

            worker.exec(query);
            worker.commit();
        }
    }
    catch (std::exception &e){
        std::cerr << e.what();
        return BAD_REQUEST;
    }

    return success;
}

int TerrainProjectsPostgres::get_terrain_params(const int &user_id, const std::string &projName, dbTerrain_t &ter)
{
    pqxx::result response;
    std::string query;
    int ret_code = SUCCESS;
    std::cerr << "GET_TERRAIN_PARAMS\n";

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT ter.width, ter.height, ter.scale, ter.octaves, ter.gain, ter.lacunarity, \
                        ter.seed, ter.frequency, ter.angle_x, ter.angle_y, ter.angle_z \
                 FROM terrain_project.terrains.terrains as ter\
                 JOIN terrain_project.terrains.projects as terProj on terProj.id_terrain = ter.id \
                 JOIN terrain_project.terrains.users_projs as usrProj on usrProj.proj_name = terProj.name \
                 WHERE usrProj.id_user = "+std::to_string(user_id)+" AND usrProj.proj_name='"+projName+"';";

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

int TerrainProjectsPostgres::delete_terrain_project(const int &userId, const std::string &projName)
{
    pqxx::result response;
    std::string query, ter_id;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try {
        pqxx::work worker(*__conn_psql);
        query = "DELETE \
                FROM terrain_project.terrains.users_projs \
                WHERE proj_name = '" + projName + "' ;";

        response = worker.exec(query);
        query = "SELECT id \
                 FROM terrain_project.terrains.terrains \
                 WHERE terrains.id = (select id_terrain \
                                      from terrain_project.terrains.projects \
                                      WHERE projects.name = '"+projName+"');";

        response = worker.exec(query);
        ter_id = response[0][0].c_str();
        std::cerr << "proj_id: " << ter_id << "\n";
        query = "DELETE \
                FROM terrain_project.terrains.projects \
                WHERE name = '" + projName + "' ;";
        response = worker.exec(query);

        query = "DELETE FROM terrain_project.terrains.terrains WHERE terrains.id=" + ter_id + ";";
        response = worker.exec(query);

        worker.commit();

        std::cerr << "Удаление проекта с ландшафтом выполнено успешно.\n";
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
