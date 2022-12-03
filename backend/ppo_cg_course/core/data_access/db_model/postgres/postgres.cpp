#include "postgres.hpp"

Postgres::Postgres(){
    __connect_psql_to_db();
    __users = std::make_unique<UserPostgres>(__connection);
    __terrains = std::make_unique<TerrainProjectsPostgres>(__connection);
    __nUsers = this->get_count_users();
    __nTerrains = this->get_count_terrains();
}


int Postgres::__connect_psql_to_db()
{
    config_t config_data;
    std::string options;

    if (__connection){
        std::cout << "Уже есть подключение к БД.\n";
        return SUCCESS;
    }

    try
    {
        config_data = __config.read_config_postgres();
        options = __config.form_options(config_data);
        __connection = std::shared_ptr<pqxx::connection>(new pqxx::connection(options));
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        return -2;
    }

    return SUCCESS;
}

int Postgres::get_count_users(){
    return __users.get()->get_count_users();
}

int Postgres::get_count_terrains(){
    return __terrains.get()->get_count_terrain_projects();
}

void Postgres::set_psql_connection(std::shared_ptr<pqxx::connection> &connection){
    __connection = connection;
}

int Postgres::get_user(const int &id, dbUsers_t &user){
    return __users.get()->get(id, user);
}

int Postgres::add_user(const dbUsers_t &user){
    return __users.get()->add(user);
}

int Postgres::update_user(const int &id, const dbUsers_t &user){
    return __users.get()->update(user.id, user);
}

int Postgres::delete_user(const int &id){
    return __users.get()->delete_user(id);
}

int Postgres::block_user(const int &id){
    return __users.get()->block(id);
}

int Postgres::unlock_user(const int &id){
    return __users.get()->unlock(id);
}

int Postgres::add_new_terrain_project(const int &userId, const std::string &terProjName){
    return __terrains.get()->add_new_terrain_project(userId, terProjName);
}

int Postgres::get_terrain_params(const int &userId, const int &terId, servTerrain_t &terParams)
{
    int ret_code = BAD_REQUEST;

    dbTerrain_t dbTerParams;
    if (userId > 0 && userId < __nUsers && terId > 0 && terId <= __nTerrains){
        ret_code = __terrains.get()->get_terrain_params(userId, terId, dbTerParams);
        __convertDbToServModel((const dbTerrain_t)dbTerParams, terParams);
    }
    return ret_code;
}

int Postgres::delete_terrain_project(const int &userId, const int &terId)
{
    int ret_code = BAD_REQUEST;
    int dbUserId, dbTerId;

    if (userId >= 0 && userId <= __nUsers && terId > 0 && terId <= __nTerrains){
        dbUserId = userId, dbTerId = terId;
        ret_code = __terrains.get()->delete_terrain_project(dbUserId, dbTerId);
    }

    return ret_code;
}

int Postgres::get_terrain_project_rating(const int &terId, double &rating){
    int ret_code = BAD_REQUEST;
    double dbRating;

    if (terId > 0 && terId <= __nTerrains){
        ret_code = __terrains.get()->get_terrain_project_rating(terId, dbRating);
        if (ret_code == SUCCESS){
            rating = dbRating;
        }
    }
    return ret_code;
}

int Postgres::set_terrain_project_rating(const int &terId, const int &rating)
{
    int ret_code = BAD_REQUEST;
    int dbRating;

    if (terId > 0 && terId <= __nTerrains && rating > 0){
        dbRating = rating;
        ret_code = __terrains.get()->set_terrain_project_rating(terId, dbRating);
    }
    return ret_code;
}

int Postgres::get_terrain_projects(const int &userId,
                                   std::vector<servTerrainProject_t> &servTerProjects)
{
    int ret_code = NOT_FOUND;
    std::vector<dbTerrainProject_t> dbTerProjects;

    if (userId > 0)
    {
        ret_code = __terrains.get()->get_terrain_projects(userId, dbTerProjects);
        if (ret_code == SUCCESS){
            __convertDbToServModel(dbTerProjects, servTerProjects);
        }
    }

    return ret_code;
}

void Postgres::__convertDbToServModel(const dbTerrain_t &dbTerParams, servTerrain_t &terParams){
    terParams.height = dbTerParams.height;
    terParams.width = dbTerParams.width;
    terParams.meta_config = dbTerParams.meta_config;
    terParams.rotate_angles = dbTerParams.rotate_angles;
    terParams.scale = dbTerParams.scale;
}

void Postgres::__convertDbToServModel(
        const std::vector<dbTerrainProject_t> &dbTerProjs, std::vector<servTerrainProject_t> &servTerProjs)
{
    if (!dbTerProjs.empty())
    {
        int nProjs = dbTerProjs.size();
        servTerProjs.resize(nProjs);

        for (int i = 0; i < nProjs; ++i){
            servTerProjs[i].id = dbTerProjs[i].id;
            servTerProjs[i].last_edit = dbTerProjs[i].last_edit;
            servTerProjs[i].name = dbTerProjs[i].name;
        }
    }
}

int Postgres::login(const std::string &login, const std::string &password, int &uuid)
{
    std::cerr << "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n";
    int success = SUCCESS;
    dbUsers_t dbUser;

    if (login.empty() || password.empty()){
        success = BAD_REQUEST;
    }
    else
    {
        dbUser.login = login;
        dbUser.password = password;

        success = __users.get()->get_validation(dbUser);
        if (success == SUCCESS && dbUser.is_blocked != "t" && dbUser.is_deleted != "t"){
            uuid = dbUser.id;
        }
    }

    return success;
}
