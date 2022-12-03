#include "mocks.hpp"
#include "error_codes.h"
#include "tests/unit_tests/data_builders/user_builder.hpp"

struct usersTest: public testing::Test
{
    std::shared_ptr<DbModel> dbModel;

    void SetUp() {
        std::shared_ptr<Postgres> postgres;
        postgres = std::make_shared<Postgres>();
        dbModel = postgres;
    }
    void TearDown() {}
};

//test fixture с AAA подходом
TEST_F(usersTest, test_get_user_login_postgres_db)
{
    dbUsers_t user;

    //Act
    dbModel->get_user(1, user);

    //Assert
    EXPECT_STREQ(user.login.c_str(), "user");
}

TEST(test_login_postgres, positive)
{
    int uuid;
    std::string login = "string", password = "string";
    std::unique_ptr<MockDb> mDb = std::make_unique<::testing::StrictMock<MockDb>>();

    EXPECT_CALL(*mDb, login(login, password, uuid))
                .Times(1)
                .WillOnce(::testing::Return(SUCCESS));
    MyDatabase myDb{std::move(mDb)};

    EXPECT_EQ(myDb.login("string", "string", uuid), SUCCESS);
}

TEST(tests_users_add_user, positive)
{
    int ret_code;
    std::unique_ptr<Admin> admin(new Admin());
    std::unique_ptr<UserBuilder> user;

    //Arrange
    user = UserBuilder().BuildDefault();
    //Act
    ret_code = admin->add_user(user->getUser());
    //Assert
    EXPECT_EQ(ret_code, SUCCESS);
}

TEST(tests_users_delete_user, positive)
{
    int ret_code;
    std::unique_ptr<Admin> admin(new Admin());
    std::unique_ptr<UserBuilder> user;

    //Arrange
    user = UserBuilder().BuildDefault();
    //Act
    ret_code = admin->delete_user(user->getUser());
    //Assert
    EXPECT_EQ(ret_code, SUCCESS);
}


TEST(tests_users_lock_user, positive)
{
    int ret_code;
    std::unique_ptr<Admin> admin(new Admin());
    std::unique_ptr<UserBuilder> user;

    //Arrange
    user = UserBuilder().BuildDefault();
    //Act
    ret_code = admin->lock_user(user->getUser());
    //Assert
    EXPECT_EQ(ret_code, SUCCESS);
}

TEST(tests_users_unlock_user, positive)
{
    int ret_code;
    std::unique_ptr<Admin> admin(new Admin());
    std::unique_ptr<UserBuilder> user;

    //Arrange
    user = UserBuilder().BuildDefault();
    //Act
    ret_code = admin->unlock_user(user->getUser());
    //Assert
    EXPECT_EQ(ret_code, SUCCESS);
}


