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

int Postgres::add_new_terrain_project(const std::string &userName, const std::string &terProjName){
    int ret_code = BAD_REQUEST;

    if (!userName.empty()){
        ret_code = __terrains.get()->add_new_terrain_project(userName, terProjName);
    }
    return ret_code;
}

int Postgres::get_terrain_params(const std::string &userName, const std::string &projName, servTerrain_t &terParams)
{
    int ret_code = BAD_REQUEST;

    dbTerrain_t dbTerParams;
    if (!userName.empty() && !projName.empty()){
        ret_code = __terrains.get()->get_terrain_params(userName, projName, dbTerParams);
        __convertDbToServModel((const dbTerrain_t)dbTerParams, terParams);
    }
    return ret_code;
}

int Postgres::delete_terrain_project(const std::string &userName, const std::string &projName)
{
    int ret_code = BAD_REQUEST;
    std::string dbProjName, dbUserName;

    if (!userName.empty()){
        dbUserName = userName;
        ret_code = __terrains.get()->delete_terrain_project(dbUserName, projName);
    }

    return ret_code;
}

int Postgres::get_terrain_project_rating(const std::string &projName, double &rating){
    int ret_code = BAD_REQUEST;
    double dbRating;

    if (!projName.empty()){
        ret_code = __terrains.get()->get_terrain_project_rating(projName, dbRating);
        if (ret_code == SUCCESS){
            rating = dbRating;
        }
    }
    return ret_code;
}

int Postgres::set_terrain_project_rating(const std::string &projName, const std::string &userName)
{
    int ret_code = BAD_REQUEST;
    int dbRating;

    if (!projName.empty() && !userName.empty()){
        ret_code = __terrains->set_terrain_project_rating(projName, userName);
    }
    return ret_code;
}

int Postgres::add_project_for_rating(const std::string &userName, const std::string &projName)
{
    int ret_code = BAD_REQUEST;

    if (!userName.empty() && !projName.empty()){
        ret_code = __terrains->add_project_for_rating(userName, projName);
    }
    return ret_code;
}

int Postgres::get_all_rating_projects(const std::string &page, std::vector<servTerrainProject_t> &terProjects)
{
    std::vector<dbTerrainProject_t> dbTerProjs;
    int ret_code = BAD_REQUEST;
    if (!page.empty()){
        ret_code = __terrains->get_all_rating_projects(page, dbTerProjs);
        __convertDbToServModel(dbTerProjs, terProjects);
    }

    return ret_code;
}

int Postgres::get_terrain_projects(const std::string &userName, int &page,
                                   std::vector<servTerrainProject_t> &servTerProjects)
{
    int ret_code = NOT_FOUND;
    std::vector<dbTerrainProject_t> dbTerProjects;

    if (!userName.empty() && page > 0)
    {
        ret_code = __terrains.get()->get_terrain_projects(userName, page, dbTerProjects);
        if (ret_code == SUCCESS){
            __convertDbToServModel(dbTerProjects, servTerProjects);
        }
    }

    return ret_code;
}

int Postgres::get_terrain_project(const std::string &projName, servTerrainProject_t &servTerProj,
                                  const std::string &userName)
{
    dbTerrainProject_t dbTerProj;
    int ret_code = NOT_FOUND;
    if (!userName.empty() && !projName.empty()){
        ret_code = __terrains->get_terrain_project(projName, dbTerProj, userName);
        if (ret_code == SUCCESS){
            __convertDbToServModel(dbTerProj, servTerProj);
        }
    }

    return ret_code;
}

int Postgres::save_terrain_params(const std::string &userName, const std::string &projName,
                                  const servTerrain_t &servTer)
{
    dbTerrain_t dbTer;
    int ret_code = NOT_FOUND;
    if (!userName.empty() && !projName.empty()){
        __convertServToDbModel(servTer, dbTer);
        ret_code = __terrains->set_terrain_params(userName, projName, dbTer);
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

void Postgres::__convertServToDbModel(const servTerrain_t &servTer, dbTerrain_t &dbTer)
{
    dbTer.width = servTer.width;
    dbTer.height = servTer.height;
    dbTer.meta_config = servTer.meta_config;
    dbTer.scale = servTer.scale;
    dbTer.rotate_angles = servTer.rotate_angles;
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
            servTerProjs[i].userName = !dbTerProjs[i].userName.empty() ? dbTerProjs[i].userName : "";
            servTerProjs[i].name = !dbTerProjs[i].name.empty() ? dbTerProjs[i].name : "";
            servTerProjs[i].last_edit = !dbTerProjs[i].last_edit.empty() ? dbTerProjs[i].last_edit : "";
            servTerProjs[i].rating = dbTerProjs[i].rating ? dbTerProjs[i].rating : 0;
        }
    }
}

void Postgres::__convertDbToServModel(const dbTerrainProject_t &dbTerProj, servTerrainProject_t &servTerProj)
{
    servTerProj.userName = dbTerProj.userName;
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
