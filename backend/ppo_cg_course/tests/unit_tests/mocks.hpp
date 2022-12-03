#ifndef _MOCKS_HPP_
#define _MOCKS_HPP_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "core/data_access/users/admin/admin.h"
#include "core/data_access/db_model/base_db_model.hpp"
#include "core/data_access/db_model/postgres/postgres.hpp"
#include "core/data_access/users/users_struct.h"

class MockDb: public DbModel
{
    public:
        MOCK_METHOD(int, login, (const std::string &login, const std::string &password, int &uuid),
                    (override));
        MOCK_METHOD(int, get_user, (const int &id, dbUsers_t &user), (override));
        MOCK_METHOD(int, add_user, (const dbUsers_t &user), (override));
        MOCK_METHOD(int, update_user, (const int &id, const dbUsers_t &user), (override));
        MOCK_METHOD(int, delete_user, (const int &id), (override));
        MOCK_METHOD(int, block_user, (const int &id), (override));
        MOCK_METHOD(int, unlock_user, (const int &id), (override));

        MOCK_METHOD(int, add_new_terrain_project, (const int &userId, const std::string &terProjName), (override));
        MOCK_METHOD(int, get_terrain_params, (const int &userId, const int &terId, servTerrain_t &terParams), (override));
        MOCK_METHOD(int, get_terrain_projects, (const int &userId, std::vector<servTerrainProject_t> &servTerProjects), (override));
        MOCK_METHOD(int, delete_terrain_project, (const int &userId, const int &terId), (override));
        MOCK_METHOD(int, get_terrain_project_rating, (const int &terId, double &rating), (override));
        MOCK_METHOD(int, set_terrain_project_rating, (const int &terId, const int &rating), (override));
};
struct MyDatabase
{
   std::unique_ptr<DbModel> myDb;

   int login(const std::string &login, const std::string &password, int &uuid){
       return myDb->login(login, password, uuid);
   }
};

#endif
