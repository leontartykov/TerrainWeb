#ifndef _BASE_DB_MODEL_HPP_
#define _BASE_DB_MODEL_HPP_

#include <vector>

#include "core/data_access/users/users_struct.h"
#include "core/data_access/terrains/terrains_struct.hpp"
#include "http_server/services/terrain/struct_terrains_service.hpp"
#include "http_server/services/user/struct_users_service.hpp"

class DbModel
{
    public:
        virtual ~DbModel() {};

        virtual int get_user(const int &id, servUsers_t &servUser) = 0;
        virtual int add_user(const servUsers_t &servUser) = 0;
        virtual int update_user(const int &id, const servUsers_t &servUser) = 0;
        virtual int delete_user(const int &id) = 0;
        virtual int delete_user(const std::string &login) = 0;
        virtual int block_user(const int &id) = 0;
        virtual int unlock_user(const int &id) = 0;

        virtual int add_new_terrain_project(const int &userId, const std::string &terProjName) = 0;
        virtual int get_terrain_params(const int &userId, const std::string &projName, servTerrain_t &terParams) = 0;
        virtual int get_terrain_projects(const int &userId, int &page, std::vector<servTerrainProject_t> &servTerProjects) = 0;
        virtual int get_terrain_project(const int &userId,  const std::string &projName, servTerrainProject_t &servTerProj) = 0;
        virtual int save_terrain_params(const int &userId, const std::string &projName, const servTerrain_t &servTer) = 0;
        virtual int delete_terrain_project(const int &userId, const std::string &projName) = 0;
        virtual int get_terrain_project_rating(const int &terId, double &rating) = 0;
        virtual int set_terrain_project_rating(const int &terId, const int &rating) = 0;

        virtual int login(const std::string &login, const std::string &password, int &uuid) = 0;
        virtual int login(const std::string &login, const std::string &password) = 0;

        //virtual int get_count_users();
        //virtual int get_count_terrains();
};

#endif
