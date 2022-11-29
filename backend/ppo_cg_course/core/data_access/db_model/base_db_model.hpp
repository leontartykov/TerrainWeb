#ifndef _BASE_DB_MODEL_HPP_
#define _BASE_DB_MODEL_HPP_

#include "core/data_access/users/users_struct.h"
#include "core/data_access/db_model/postgres/postgres_data/postgres_terrains/postgres_terrains.h"

class DbModel
{
    public:
        virtual ~DbModel() = 0;
        virtual int get_user(int &id, users_t &user) = 0;
        virtual int add_user(users_t &user) = 0;
        virtual int update_user(int &id, users_t &user) = 0;
        virtual int delete_user(int &id) = 0;
        virtual int block_user(int &id) = 0;
        virtual int unlock_user(int &id) = 0;

        virtual int add_new_terrain_project(std::string &terProjName, int &userId) = 0;
        virtual int get_terrain_project(terrain_project &terProj, int &userId) = 0;
        virtual std::pair<int, std::vector<terrain_project_t>> get_terrain_projects(int &userId) = 0;
        virtual int delete_terrain_project(int &terId, int &userId) = 0;
        virtual double get_terrain_project_rating(int &terId) = 0;
        virtual int set_terrain_project_rating(int &terId, int &rating) = 0;

};

#endif
