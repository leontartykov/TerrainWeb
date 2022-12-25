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
        MOCK_METHOD(int, login, (const std::string &login, const std::string &password),
                    (override));

        MOCK_METHOD(int, get_user, (const int &id, servUsers_t &user), (override));
        MOCK_METHOD(int, add_user, (const servUsers_t &user), (override));
        MOCK_METHOD(int, update_user, (const int &id, const servUsers_t &user), (override));
        MOCK_METHOD(int, delete_user, (const int &id), (override));
        MOCK_METHOD(int, delete_user, (const std::string &login), (override));
        MOCK_METHOD(int, block_user, (const int &id), (override));
        MOCK_METHOD(int, unlock_user, (const int &id), (override));

        MOCK_METHOD(int, add_new_terrain_project, (const std::string &userName, const std::string &terProjName), (override));
        MOCK_METHOD(int, get_terrain_params, (const std::string &userName, const std::string &projName, servTerrain_t &terParams), (override));
        MOCK_METHOD(int, get_terrain_projects, (const std::string &userName, int &page, std::vector<servTerrainProject_t> &servTerProjects), (override));
        MOCK_METHOD(int, save_terrain_params, (const std::string &userName, const std::string &projName, const servTerrain_t &servTer), (override));
        MOCK_METHOD(int, get_terrain_project, (const std::string &projName, servTerrainProject_t &servTerProjects, const std::string &userName), (override));
        MOCK_METHOD(int, delete_terrain_project, (const std::string &userName, const std::string &projName), (override));
        MOCK_METHOD(int, get_terrain_project_rating, (const std::string &projName, double &rating), (override));
        MOCK_METHOD(int, set_terrain_project_rating, (const std::string &projName, const std::string &userName), (override));
        MOCK_METHOD(int, add_project_for_rating, (const std::string &userName, const std::string &projName), (override));
        MOCK_METHOD(int, get_all_rating_projects, (const std::string &page, std::vector<servTerrainProject_t> &terProjects), (override));
};
struct MyDatabase
{
   std::unique_ptr<DbModel> myDb;

   int login(const std::string &login, const std::string &password, int &uuid){
       return myDb->login(login, password, uuid);
   }

   int delete_user(const std::string &login){
       return myDb->delete_user(login);
   }
};

#endif
