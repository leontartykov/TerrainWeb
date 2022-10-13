#include <gtest/gtest.h>

#include "../core/data_access/users/admin/admin.h"

TEST(tests_users_add_user, positive)
{
    int result = 0;
    std::unique_ptr<Admin> admin(new Admin());

    users_t user = {.id = 1,
                    .login = "user_1",
                    .password = "ur21",
                    .is_blocked="false",
                    .is_deleted="false"};
    int error = admin->add_user(user);

    EXPECT_EQ(error, result);
}

TEST(tests_users_delete_user, positive)
{
    int result = 0;
    std::unique_ptr<Admin> admin(new Admin());

    users_t user = {.id = 1,
                    .login = "user_1",
                    .password = "ur21",
                    .is_blocked="false",
                    .is_deleted="false"};
    int error = admin->delete_user(user);

    EXPECT_EQ(error, result);
}


TEST(tests_users_lock_user, positive)
{
    int result = 0;
    std::unique_ptr<Admin> admin(new Admin());

    users_t user = {
        .id = 1,
        .login = "user_1",
        .password = "ur21",
        .is_blocked="false",
        .is_deleted="false"
    };
    int error = admin->lock_user(user);

    EXPECT_EQ(error, result);
}

TEST(tests_users_unlock_user, positive)
{
    int result = 0;
    std::unique_ptr<Admin> admin(new Admin());

    users_t user = {
        .id = 1,
        .login = "user_1",
        .password = "ur21",
        .is_blocked="false",
        .is_deleted="false"
    };
    int error = admin->unlock_user(user);

    EXPECT_EQ(error, result);
}


