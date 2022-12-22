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

int Postgres::get_user(const int &id, servUsers_t &servUser){
    dbUsers_t dbUser;
    int ret_code = BAD_REQUEST;

    if (id > 0){
        ret_code = __users.get()->get(id, dbUser);
        __convertDbToServModel(dbUser, servUser);
    }

    return ret_code;
}

int Postgres::add_user(const servUsers_t &servUser){
    dbUsers_t dbUser;
    int ret_code = BAD_REQUEST;

    if (!servUser.login.empty() && !servUser.password.empty() && servUser.perm_level >= 0){
        __convertServToDbModel(servUser, dbUser);
        ret_code = __users.get()->add(dbUser);
    }
    return ret_code;
}

int Postgres::update_user(const int &id, const servUsers_t &servUser){
    dbUsers_t dbUser;
    int ret_code = BAD_REQUEST;

    if (id >= 0 && id < __nUsers){
        __convertServToDbModel(servUser, dbUser);
        ret_code = __users.get()->update(dbUser.id, dbUser);
    }
    return ret_code;
}

int Postgres::delete_user(const int &id){
    int ret_code = BAD_REQUEST;

    if (id >= 0 && id < __nUsers){
        ret_code = __users.get()->delete_user(id);
    }
    return ret_code;
}

int Postgres::delete_user(const std::string &login)
{
    int ret_code = BAD_REQUEST;

    if (!login.empty()){
        ret_code = __users->delete_user(login);
    }

    return ret_code;
}

int Postgres::block_user(const int &id){
    int ret_code = BAD_REQUEST;

    if (id >= 0 && id < __nUsers){
        ret_code = __users->block(id);
    }
    return ret_code;
}

int Postgres::unlock_user(const int &id){
    int ret_code = BAD_REQUEST;

    if (id >= 0 && id < __nUsers){
        ret_code = __users.get()->unlock(id);
    }
    return ret_code;
}

int Postgres::add_new_terrain_project(const int &userId, const std::string &terProjName){
    int ret_code = BAD_REQUEST;

    if (userId >= 0 && userId < __nUsers){
        ret_code = __terrains.get()->add_new_terrain_project(userId, terProjName);
    }
    return ret_code;
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

int Postgres::delete_terrain_project(const int &userId, const std::string &projName)
{
    int ret_code = BAD_REQUEST;
    int dbUserId;
    std::string dbProjName;

    if (userId >= 0 && userId <= __nUsers){
        dbUserId = userId;
        ret_code = __terrains.get()->delete_terrain_project(dbUserId, projName);
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

int Postgres::get_terrain_projects(const int &userId, int &page,
                                   std::vector<servTerrainProject_t> &servTerProjects)
{
    int ret_code = NOT_FOUND;
    std::vector<dbTerrainProject_t> dbTerProjects;

    if (userId > 0 && page > 0)
    {
        ret_code = __terrains.get()->get_terrain_projects(userId, page, dbTerProjects);
        if (ret_code == SUCCESS){
            __convertDbToServModel(dbTerProjects, servTerProjects);
        }
    }

    return ret_code;
}

int Postgres::get_terrain_project(const int &userId, const std::string &projName, servTerrainProject_t &servTerProj)
{
    dbTerrainProject_t dbTerProj;
    int ret_code = NOT_FOUND;
    if (userId > 0 && !projName.empty()){
        ret_code = __terrains->get_terrain_project(userId, projName, dbTerProj);
        if (ret_code == SUCCESS){
            __convertDbToServModel(dbTerProj, servTerProj);
        }
    }

    return ret_code;
}

void Postgres::__convertDbToServModel(const dbUsers_t &dbUser, servUsers_t &servUser)
{
    servUser.id = dbUser.id;
    servUser.login = dbUser.login;
    servUser.password = dbUser.password;
    servUser.perm_level = dbUser.perm_level;
    servUser.is_blocked = dbUser.is_blocked;
    servUser.is_deleted = dbUser.is_deleted;
}

void Postgres::__convertServToDbModel(const servUsers_t &servUser, dbUsers_t &dbUser)
{
    dbUser.login = servUser.login;
    dbUser.password = servUser.password;
    dbUser.perm_level = servUser.perm_level;
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
            servTerProjs[i].name = dbTerProjs[i].name;
            servTerProjs[i].last_edit = dbTerProjs[i].last_edit;
        }
    }
}

void Postgres::__convertDbToServModel(const dbTerrainProject_t &dbTerProj, servTerrainProject_t &servTerProj)
{
    servTerProj.name = dbTerProj.name;
    servTerProj.last_edit = dbTerProj.last_edit;
    servTerProj.rating = dbTerProj.rating;
    servTerProj.n_rates = dbTerProj.n_rates;
    servTerProj.exhibited = dbTerProj.exhibited;
}

int Postgres::login(const std::string &login, const std::string &password, int &uuid)
{
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

int Postgres::login(const std::string &login, const std::string &password){
    int uuid = 0;
    return this->login(login, password, uuid);
}
