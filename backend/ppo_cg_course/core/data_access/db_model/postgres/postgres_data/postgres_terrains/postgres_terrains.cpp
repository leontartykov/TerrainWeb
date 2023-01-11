#include "postgres_terrains.h"

TerrainProjectsPostgres::TerrainProjectsPostgres(std::shared_ptr<pqxx::connection> &conn_psql,
                                                 const std::string &dbName){
    __dbName = dbName;
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
        query = "SELECT COUNT(*) FROM "+__dbName+".terrains.projects";
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
    std::string query = "UPDATE "+__dbName+".terrains.terrains SET ('" + \
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
                         "WHERE "+__dbName+".terrains.terrains = " + project_name + "';'";
    worker.exec(query);
    worker.commit();
}

///Return all user terrain projects
int TerrainProjectsPostgres::get_terrain_projects(const std::string &userName, int &page,
                                                  std::vector<dbTerrainProject_t> &dbTerProjs)
{
    std::string pageCard = std::to_string(page);
    pqxx::work worker(*__conn_psql);
    pqxx::result response;
    int ret_code = SUCCESS;
    int count_ter_projs;
    std::string query;

    query = "SELECT ter_projs.name, ter_projs.last_edited \
                        FROM "+__dbName+".terrains.projects as ter_projs \
                        JOIN "+__dbName+".terrains.users_projs as ter_user \
                             on ter_projs.name = ter_user.proj_name \
                        JOIN "+__dbName+".users.info as info \
                             on info.id = ter_user.id_user \
                        WHERE info.login = '" + userName +
                        "' ORDER BY ter_projs.last_edited DESC, ter_projs.id_terrain DESC \
                        LIMIT 3 OFFSET "+ std::to_string((page-1)*3) + ";";
    try{
        response = worker.exec(query);

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

int TerrainProjectsPostgres::get_terrain_project(const std::string &projName, dbTerrainProject_t &dbTerProj,
                                                 const std::string &userName)
{
    pqxx::work worker(*__conn_psql);
    pqxx::result response;
    int ret_code = SUCCESS;
    std::string query;

    std::cerr << "userName: " << userName << "\n";
    std::cerr << "__dbName: " << __dbName << "\n";
    if (userName != "----"){
        query = "SELECT login, name, last_edited, rating, n_rates, exhibited \
                FROM "+__dbName+".terrains.projects \
                JOIN "+__dbName+".terrains.users_projs on projects.name = users_projs.proj_name\
                JOIN "+__dbName+".users.info on info.id = users_projs.id_user \
                WHERE projects.name ='"+projName+"' AND info.login = '"+userName+"';";
    }
    else{
        query = "SELECT login, name, last_edited, rating, n_rates, exhibited \
                 FROM "+__dbName+".terrains.projects \
                 JOIN "+__dbName+".terrains.users_projs on projects.name = users_projs.proj_name \
                 JOIN "+__dbName+".users.info on info.id = users_projs.id_user \
                 WHERE projects.name ='" + projName + "';";
    }


    try{
        response = worker.exec(query);
        std::cerr << "HAHAHAHA\n";
        std::cerr << "response.size = " << response.size() << "\n";
        if (response.size() == 0){
            ret_code = NOT_FOUND;
        }
        else{
            dbTerProj.userName = response[0][0].is_null() ? "" : response[0][0].c_str();
            dbTerProj.name = response[0][1].c_str();
            dbTerProj.last_edit = response[0][2].c_str();
            dbTerProj.rating = response[0][3].is_null() ? 0 : response[0][3].as<double>();
            dbTerProj.n_rates = response[0][4].is_null() ? 0 : response[0][4].as<int>();
            dbTerProj.exhibited = response[0][5].is_null() ? false : response[0][5].as<bool>();
        }
        //else if (userName != "----"){
        /*}
        else{
            std::cerr << "response[0][0].c_str(): " << response[0][0].c_str() << "\n";
            dbTerProj.userName = response[0][0].c_str();
            dbTerProj.name = response[0][1].c_str();
            dbTerProj.last_edit = response[0][2].c_str();
            dbTerProj.rating = response[0][3].is_null() ? 0 : response[0][3].as<double>();
            dbTerProj.n_rates = response[0][4].is_null() ? 0 : response[0][4].as<int>();
            dbTerProj.exhibited = response[0][5].is_null() ? false : response[0][5].as<bool>();
        }*/
    }
    catch(std::exception &e){
        std::cerr << e.what();
        return BAD_REQUEST;
    }
    std::cerr << "ret_code_end: " << ret_code << "\n";

    return ret_code;
}

int TerrainProjectsPostgres::get_count_terrain_projects(){
    return __count_terrain_projs;
}

int TerrainProjectsPostgres::set_terrain_params(
        const std::string &userName, const std::string &projName, const dbTerrain_t &ter)
{
    pqxx::result response;
    std::string query;
    int success = SUCCESS;
    pqxx::work worker(*__conn_psql);
    std::string id_terrain;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    query = "SELECT id_terrain \
             FROM "+__dbName+".terrains.users_projs \
             JOIN "+__dbName+".terrains.projects ON users_projs.proj_name = projects.name \
             JOIN "+__dbName+".users.info ON users_projs.id_user = info.id \
             WHERE info.login = '"+userName+"' AND users_projs.proj_name = '"+projName+"';";
    try{
        response = worker.exec(query);
        if (!response[0][0].is_null()){
            id_terrain = response[0][0].c_str();
            std::cerr << "id_terrain: " << id_terrain << "\n";
            query = "UPDATE "+__dbName+".terrains.terrains SET \
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

int TerrainProjectsPostgres::add_new_terrain_project(const std::string &userName, const std::string &terProjName)
{
    std::string query, newTerId, userId;
    int success = SUCCESS_CREATED;
    pqxx::result response;
    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    pqxx::work worker(*__conn_psql);
    try{
        query = "SELECT COUNT(*) \
                 FROM "+__dbName+".terrains.users_projs \
                 WHERE proj_name='" + terProjName + "';";
        response = worker.exec(query);
        std::cerr << "response[0][0].as<int>(): " << response[0][0].as<int>() << "\n";
        if (response[0][0].as<int>() == 1){
            success = CONFLICT;
        }
        else{
            query = "SELECT MAX(id) from "+__dbName+".terrains.terrains;";
            response = worker.exec(query);

            newTerId = (response[0][0].is_null()) ? "1" : std::to_string(response[0][0].as<int>() + 1);
            std::cerr << "newTerId: " << newTerId << "\n";

            query = "INSERT INTO "+__dbName+".terrains.terrains VALUES (" +
                                newTerId + ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);";

            __count_terrain_projs++;

            worker.exec(query);

            query = "INSERT INTO "+__dbName+".terrains.projects VALUES ('"
                    + terProjName + "', " + "'today', null, null, null, " + newTerId + ");";

            worker.exec(query);

            std::cerr << "userName: " << userName << "\n";
            query = "SELECT info.id \
                     FROM "+__dbName+".users.info \
                     WHERE info.login='" + userName + "';";
            response = worker.exec(query);
            std::cerr << "response[0][0].c_str(): " << response[0][0].c_str() << "\n";
            userId = (response[0][0].is_null()) ? throw : response[0][0].c_str();
            std::cerr << "userId: " << userId << "\n";

            query = "INSERT INTO "+__dbName+".terrains.users_projs VALUES (" +
                    userId + ", '" + terProjName + "');";

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

int TerrainProjectsPostgres::get_terrain_params(const std::string &userName, const std::string &projName, dbTerrain_t &ter)
{
    pqxx::result response;
    std::string query;
    int ret_code = SUCCESS;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT ter.width, ter.height, ter.scale, ter.octaves, ter.gain, ter.lacunarity, \
                        ter.seed, ter.frequency, ter.angle_x, ter.angle_y, ter.angle_z \
                 FROM "+__dbName+".terrains.terrains as ter\
                 JOIN "+__dbName+".terrains.projects as terProj on terProj.id_terrain = ter.id \
                 JOIN "+__dbName+".terrains.users_projs as usrProj on usrProj.proj_name = terProj.name \
                 JOIN "+__dbName+".users.info ON info.id = usrProj.id_user \
                 WHERE info.login = '"+userName+"' AND usrProj.proj_name='"+projName+"';";

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

int TerrainProjectsPostgres::get_terrain_params(const std::string &projName, dbTerrain_t &ter)
{
    pqxx::result response;
    std::string query;
    int ret_code = SUCCESS;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT ter.width, ter.height, ter.scale, ter.octaves, ter.gain, ter.lacunarity, \
                        ter.seed, ter.frequency, ter.angle_x, ter.angle_y, ter.angle_z \
                 FROM "+__dbName+".terrains.terrains \
                 JOIN "+__dbName+".terrains.projects on projects.id_terrain = terrains.id \
                 WHERE projects.name = '"+projName+"';";

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

int TerrainProjectsPostgres::delete_terrain_project(const std::string &userName, const std::string &projName)
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
                FROM "+__dbName+".terrains.users_projs \
                WHERE proj_name = '" + projName + "' ;";

        response = worker.exec(query);
        query = "SELECT id \
                 FROM "+__dbName+".terrains.terrains \
                 WHERE terrains.id = (select id_terrain \
                                      from "+__dbName+".terrains.projects \
                                      WHERE projects.name = '"+projName+"');";

        response = worker.exec(query);
        ter_id = response[0][0].c_str();
        std::cerr << "proj_id: " << ter_id << "\n";
        query = "DELETE \
                FROM "+__dbName+".terrains.projects \
                WHERE name = '" + projName + "' ;";
        response = worker.exec(query);

        query = "DELETE FROM "+__dbName+".terrains.terrains WHERE terrains.id=" + ter_id + ";";
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

double TerrainProjectsPostgres::get_terrain_project_rating(const std::string &projName, double &dbRating)
{
    pqxx::result response;
    std::string query, ter_id;
    int ret_code = SUCCESS;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT rating\
                 FROM "+__dbName+".terrains.projects \
                 WHERE id = " + ter_id + " AND exhibited = true;";
        response = worker.exec(query);

        if (!response.empty()){
            dbRating = std::stoi(response[0][0].c_str());
        }
        else{
            ret_code = NOT_FOUND;
        }
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
        return BAD_REQUEST;
    }

    return ret_code;
}

int TerrainProjectsPostgres::set_terrain_project_rating(const std::string &projName, const std::string &userName)
{
    pqxx::result response;
    std::string query, user_id;
    int response_code = SUCCESS;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT id \
                 FROM "+__dbName+".users.info \
                 WHERE info.login ='"+userName+"';";
        response = worker.exec(query);

        if (response.size()){
            user_id = response[0][0].c_str();
            std::cerr << "user_id: " << user_id << "\n";
            query = "UPDATE "+__dbName+".terrains.projects \
                     SET rating=rating+1 \
                     FROM "+__dbName+".terrains.users_projs \
                     WHERE id_user= " + user_id + "AND proj_name ='"+projName+"' AND exhibited = true;";
            worker.exec(query);
            worker.commit();
        }
        else{
            response_code = NOT_FOUND;
        }
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
        return BAD_REQUEST;
    }

    return response_code;
}

int TerrainProjectsPostgres::add_project_for_rating(const std::string &userName, const std::string &projName)
{
    pqxx::result response;
    std::string query, user_id;
    int response_code = SUCCESS;

    std::cerr << "add_project_for_rating\n";
    if (!__conn_psql){
        std::cerr << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }
    query = "SELECT info.id \
             FROM "+__dbName+".users.info \
             WHERE info.login = '"+userName+"';";

    try{
        pqxx::work worker(*__conn_psql);
        response = worker.exec(query);

        user_id = response[0][0].is_null() ? throw : response[0][0].c_str();
        query = "UPDATE "+__dbName+".terrains.projects \
                 SET exhibited = true rating=0\
                 FROM terrains.users_projs \
                 WHERE users_projs.id_user = "+user_id+" AND projects.name='"+ projName +"';";
        worker.exec(query);
        worker.commit();
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
        return BAD_REQUEST;
    }

    return response_code;
}

int TerrainProjectsPostgres::get_all_rating_projects(
        const std::string &page, std::vector<dbTerrainProject_t> &dbTerProjs)
{
    pqxx::result response;
    std::string query, user_id;
    int ret_code = SUCCESS, count_ter_projs;

    if (!__conn_psql){
        std::cerr << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }

    query = "SELECT login, name, last_edited, rating \
             FROM "+__dbName+".terrains.projects \
             JOIN "+__dbName+".terrains.users_projs on users_projs.proj_name = projects.name \
             JOIN "+__dbName+".users.info on users_projs.id_user = info.id\
             WHERE projects.exhibited = true \
             LIMIT 3 OFFSET "+ std::to_string((std::stoi(page)-1)*3) + ";";
    try{
        pqxx::work worker(*__conn_psql);
        response = worker.exec(query);
        std::cerr << "response.size = " << response.size() << "\n";

        if (response.empty()){
            ret_code = SUCCESS;
        }
        else{
            count_ter_projs = response.size();
            dbTerProjs.resize(count_ter_projs);
            for (int i = 0; i < count_ter_projs; ++i){
                dbTerProjs[i].userName = response[i][0].c_str();
                dbTerProjs[i].name = response[i][1].c_str();
                dbTerProjs[i].last_edit = response[i][2].c_str();
                dbTerProjs[i].rating = !response[i][3].is_null() ? response[i][3].as<double>() : 0;
            }
        }
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
        return BAD_REQUEST;
    }

    return ret_code;
}
