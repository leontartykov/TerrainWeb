#include "postgres_terrains.h"

TerrainProjectsPostgres::TerrainProjectsPostgres(std::shared_ptr<pqxx::connection> &conn_psql){
    __conn_psql = conn_psql;
    __define_count_terrain_projects();
}

void TerrainProjectsPostgres::__define_count_terrain_projects()
{
    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return;
    }

    try{
        pqxx::work worker(*__conn_psql);
        std::string query = "SELECT COUNT(*) FROM terrain_project.terrains.projects";
        pqxx::result response = worker.exec(query);
        __count_terrain_projs = std::stoi(response[0][0].c_str());
    }
    catch(std::exception const &e){
        std::cout << e.what() << '\n';
    }
}

void TerrainProjectsPostgres::set_terrain_params(std::string &project_name, terrain_t &terrain_params){
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
std::pair<int, std::vector<terrain_project_t>> TerrainProjectsPostgres::get_terrain_projects(int &user_id)
{
    std::vector<terrain_project_t> ter_projs;
    std::string id_user = std::to_string(user_id);
    pqxx::work worker(*__conn_psql);
    pqxx::result response;
    int http_response_code = 0;
    int count_ter_projs;

    std::string query = "SELECT ter_projs.id, ter_projs.name, ter_projs.last_edited \
                        FROM terrain_project.terrains.projects as ter_projs \
                        JOIN terrain_project.terrains.terrains_users as ter_user \
                             on ter_projs.id = ter_user.id_terrain \
                        JOIN terrain_project.users.info as info \
                             on info.id = ter_user.id_user where id_user = " + id_user + ";";
    response = worker.exec(query);
    std::cout << "response.size() = " << response.size() << "\n";

    if (response.size() == 0){
        http_response_code = 404;
    }
    else{
        http_response_code = 200;
        count_ter_projs = response.size();
        ter_projs.resize(count_ter_projs);
        for (int i = 0; i < count_ter_projs; ++i){
            ter_projs[i].id = response[i][0].as<int>();
            ter_projs[i].name = response[i][1].c_str();
            ter_projs[i].last_edit = response[i][2].c_str();
        }
    }

    return {http_response_code, ter_projs};
}

int TerrainProjectsPostgres::get_count_terrain_projects(){
    return __count_terrain_projs;
}

int TerrainProjectsPostgres::add_new_terrain_project(terrain_project_t &ter_proj, int &user_id)
{
    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return -1;
    }

    pqxx::work worker(*__conn_psql);
    std::string query = "INSERT INTO terrain_project.terrains.terrains VALUES (" +
                        std::to_string(ter_proj.id) + ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);";

    __count_terrain_projs++;

    worker.exec(query);

    query = "INSERT INTO terrain_project.terrains.projects VALUES (" +
            std::to_string(ter_proj.id) + ", '" + ter_proj.name + "', " + "'2022-01-01', " +
            std::to_string(ter_proj.id) + ");";

    worker.exec(query);

    query = "INSERT INTO terrain_project.terrains.terrains_users VALUES (" +
            std::to_string(user_id) + ", " + std::to_string(ter_proj.id) + ");";

    worker.exec(query);
    worker.commit();

    return 201;
}

int TerrainProjectsPostgres::get_terrain_project(terrain_project &ter_proj, int &user_id)
{
    pqxx::result response;
    std::string query;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return -1;
    }

    pqxx::work worker(*__conn_psql);
    query = "SELECT ter.width, ter.height, ter.scale, ter.octaves, ter.gain, ter.lacunarity, \
                    ter.seed, ter.frequency, ter.angle_x, ter.angle_y, ter.angle_z \
             FROM terrain_project.terrains.projects as proj\
                  JOIN terrain_project.terrains.terrains as ter on \
                       proj.id_terrain = ter.id \
                  JOIN terrain_project.terrains.terrains_users as ter_usr \
                       on ter_usr.id_terrain = proj.id_terrain \
             WHERE ter_usr.id_user = " + std::to_string(user_id) + ";";

    response = worker.exec(query);
    ter_proj.terrain.width = response[0][0].as<int>();
    ter_proj.terrain.height = response[0][1].as<int>();
    ter_proj.terrain.scale = response[0][2].as<double>();
    ter_proj.terrain.meta_config.octaves = response[0][3].as<int>();
    ter_proj.terrain.meta_config.gain = response[0][4].as<double>();
    ter_proj.terrain.meta_config.lacunarity = response[0][5].as<double>();
    ter_proj.terrain.meta_config.seed = response[0][6].as<int>();
    ter_proj.terrain.meta_config.frequency = response[0][7].as<double>();
    ter_proj.terrain.rotate_angles.angle_x = response[0][8].as<int>();
    ter_proj.terrain.rotate_angles.angle_y = response[0][9].as<int>();
    ter_proj.terrain.rotate_angles.angle_z = response[0][10].as<int>();

    return 0;
}

int TerrainProjectsPostgres::delete_terrain_project(terrain_project &ter_proj, int &user_id)
{
    pqxx::result response;
    std::string query;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return -1;
    }

    pqxx::work worker(*__conn_psql);
    query = "DELETE \
            FROM terrain_project.terrains.terrains_users \
            WHERE id_user = " + std::to_string(user_id) + " ;" +

            "DELETE \
            FROM terrain_project.terrains.projects \
            WHERE id = " + std::to_string(ter_proj.id) + " ;" +

            "DELETE \
            FROM terrain_project.terrains.terrains \
            WHERE id = " + std::to_string(ter_proj.id) + " ; ";

    response = worker.exec(query);
    worker.commit();

    std::cout << "Удаление проекта с ландшафтом выполнено успешно.\n";

    return 0;
}
