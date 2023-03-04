cmake_minimum_required(VERSION 3.5)

project(ppo_cg_course LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++20 -DQT_NO_VERSION_TAGGING")

include(GoogleTest)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Network COMPONENTS QtNetwork REQUIRED)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR your_path_to_mysql_connectorcpp)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/cppconn)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

set(
    GEOMETRY_ENGINE

    core/geometry/point/point_base.h
    core/geometry/point/point_3d.h
    core/geometry/point/point_3d.hpp
    core/geometry/point/point_3d.cpp

    core/geometry/point/point_2d.h
    core/geometry/point/point_2d.hpp
    core/geometry/point/point_2d.cpp

    core/geometry/vector/vector_3d.h
    core/geometry/vector/vector_3d.hpp

    core/geometry/triangle/triangle_3d.h
    core/geometry/triangle/triangle_3d.hpp
    core/geometry/triangle/triangle_3d.cpp

    core/geometry/plane/plane.h
    core/geometry/plane/plane.cpp
)

set(
    HEIGHTMAP_ENGINE

    core/heightmap/base_noise.h
    core/heightmap/perlin_noise/perlin_noise_struct.h
    core/heightmap/perlin_noise/perlin_original.h
    core/heightmap/perlin_noise/perlin_original.hpp
    core/heightmap/perlin_noise/perlin_original.cpp
)

set(
    OBJECTS_ENGINE

    core/object/object_base.h

    core/object/terrain/base_terrain.h

    core/object/terrain/terrain_struct.h
    core/object/terrain/terrain.h
    core/object/terrain/terrain.hpp
    core/object/terrain/terrain.cpp

    core/object/terrain/terrain_commands/terrain_commands.h
    core/object/terrain/terrain_commands/terrain_commands.cpp

    core/object/terrain/terrain_facade/terrain_facade.h
    core/object/terrain/terrain_facade/terrain_facade.cpp

    core/object/light/light.h
    core/object/light/light.cpp
)

set(
    SCENE_ENGINE

    core/scene/base_scene.hpp

    core/scene/scene_struct.h

    core/scene/scene.h
    core/scene/scene.cpp

    core/scene/scene_facade/scene_facade.h
    core/scene/scene_facade/scene_facade.cpp

    core/scene/scene_commands/scene_command_base.h
    core/scene/scene_commands/scene_command_base.cpp
    core/scene/scene_commands/scene_commands.cpp
    core/scene/scene_commands/scene_commands.h
)

set(
    HIDDEN_LINES_AND_PLAINS_ENGINE

    core/invisible/zbuffer/zbuffer_base.h
    core/invisible/zbuffer/zbuffer.h
    core/invisible/zbuffer/zbuffer.hpp
    core/invisible/zbuffer/zbuffer.cpp
)

set(
    OBJECT_TRANSFORM_ENGINE

    core/transform/transform.h
    core/transform/transform.cpp
)

set(
    TERRAIN_ENGINE

    ${GEOMETRY_ENGINE}
    ${HEIGHTMAP_ENGINE}
    ${OBJECTS_ENGINE}
    ${SCENE_ENGINE}
    ${HIDDEN_LINES_AND_PLAINS_ENGINE}
    ${OBJECT_TRANSFORM_ENGINE}
)

set(
    GUI_ENGINE

    core/gui/main_window.cpp
    core/gui/main_window.h
    core/gui/mainwindow.ui
)

set(
    ENTRY_ENGINE

    core/entry/entry.h
    core/entry/entry.cpp

    core/entry/app_command/app_command_base.h
    core/entry/app_command/app_command.h
    core/entry/app_command/app_command.hpp
    core/entry/app_command/app_command.cpp

    core/entry/app_facade/app_facade.h
    core/entry/app_facade/app_facade.cpp

    core/entry/user_fabric/user_creator.h
    core/entry/user_fabric/user_creator.hpp
    core/entry/user_fabric/user_fabric.h
    core/entry/user_fabric/user_solution.hpp
)

set(
    IMAGES_ENGINE

    core/data_access/images/base_image.hpp

    core/data_access/images/data_access_image_bmp.h
    core/data_access/images/data_access_image_bmp.hpp
    core/data_access/images/data_access_image_bmp.cpp
    core/data_access/images/bmp_structure.h

    core/data_access/images/png/png.hpp
    core/data_access/images/png/png.cpp
)

set(
    POSTGRES_ENGINE

    core/data_access/db_model/postgres/postgres.hpp
    core/data_access/db_model/postgres/postgres.cpp

    core/data_access/db_model/postgres/postgres_data/postgres_users/postgres_user.h
    core/data_access/db_model/postgres/postgres_data/postgres_users/postgres_user.cpp
    core/data_access/db_model/postgres/postgres_data/postgres_terrains/postgres_terrains.h
    core/data_access/db_model/postgres/postgres_data/postgres_terrains/postgres_terrains.cpp
)

set(
    REDIS_ENGINE

    core/data_access/redis/sessions.hpp
    core/data_access/redis/sessions.cpp
)

set(
    LOG_ENGINE

    core/log_app/log_app.h
    core/log_app/log_app.cpp
    core/log_app/log_structs.h
)

set(
    DATA_ACCESS_COMPONENT

    ${REPOSITORY}
)

set(
    CONFIG_ENGINE

    core/config/base_config.hpp
    core/config/config_struct.h
    core/config/config.h
    core/config/config.cpp
)

set(
    REPOSITORY_USERS

    core/data_access/users/base_user.h
    core/data_access/users/users_struct.h

    core/data_access/users/admin/admin.h
    core/data_access/users/admin/admin.cpp
    core/data_access/users/admin/admin_menu.cpp

    core/data_access/users/user/users.h
    core/data_access/users/user/users.cpp
)

set(
    REPOSITORY_TERRAINS

    core/data_access/terrains/terrains_struct.hpp
)

set(
    REPOSITORY_FILES

    core/data_access/data_access_file/data_access_file_base.h
    core/data_access/data_access_file/data_access_file.h
    core/data_access/data_access_file/data_access_file.hpp
)

set(
    REPOSITORY

    ${REPOSITORY_USERS}
    ${REPOSITORY_TERRAINS}
    ${REPOSITORY_FILES}


    core/data_access/db_model/base_db_model.hpp

    core/data_access/data_interfaces/interface_users_db.h
)

set(
    EXCEPTION_ENGINE

    core/exceptions/base_error.h
    core/exceptions/errors.h
)

set(
    JWT_ENGINE

    server/jwt/jwt.hpp
    server/jwt/jwt.cpp
)

set(
    UNIT_TESTS

    tests/unit_tests/mocks.hpp
    tests/unit_tests/data_builders/user_builder.hpp
    tests/unit_tests/data_builders/point3D_builder.hpp
    tests/unit_tests/data_builders/vector3D_builder.hpp
    tests/unit_tests/data_builders/terrain_builder.hpp

    tests/unit_tests/tests_point_3d.cpp
    tests/unit_tests/tests_vector_3d.cpp
    tests/unit_tests/tests_perlin_noise.cpp
    tests/unit_tests/tests_zbuffer.cpp
    tests/unit_tests/tests_plane.cpp
    tests/unit_tests/tests_file.cpp
    tests/unit_tests/tests_image.cpp
    tests/unit_tests/tests_users.cpp

    tests/integration_tests/tests_image.cpp

    http_server/services/terrain/terrains_service.cpp
)

set(
    INTEGRATION_TESTS

    tests/integration_tests/tests_image.cpp

    http_server/services/terrain/terrains_service.cpp
)

set(
    TESTS
    ${UNIT_TESTS}
    ${INTEGRATION_TESTS}
)

set(
    ERROR_ENGINE

    error_codes.h
)

set(
    SERVER_SOURCERS

    #server/http_server/http_server.h
    #server/http_server/http_server.cpp

    #server/http2_server/http2_server.h
    #server/http2_server/http2_server.cpp

    #server/async_con.h
    #server/async_con.cpp
    #server/controllers/server_handlers.cpp

    ${ERROR_ENGINE}
    ${JWT_ENGINE}
    ${CONFIG_ENGINE}
    ${POSTGRES_ENGINE}
    ${REDIS_ENGINE}
    ${REPOSITORY_USERS}

    server/json_former/json_former.hpp
    server/json_former/json_former.cpp

    core/data_access/data_interfaces/interface_users_db.h

    server/logs/access/access_log.hpp
    server/logs/access/access_log.cpp
    server/logs/error/error_log.hpp
    server/logs/error/error_log.cpp
)

find_package(Drogon CONFIG REQUIRED)
set (
    HTTP_SERVER
    http_server/http_server_10/http_server_10.hpp
    http_server/http_server_10/http_server_10.cpp

    http_server/controllers/http_controllers.hpp

    http_server/controllers/terrains/terrain_controller.cpp
    http_server/controllers/users/user_controller.cpp

    http_server/services/base_terrain_service.hpp
    http_server/services/base_user_service.hpp
    http_server/services/user/struct_users_service.hpp
    http_server/services/user/users_service.cpp
    http_server/services/user/users_service.hpp
    http_server/services/terrain/struct_terrains_service.hpp
    http_server/services/terrain/terrains_service.hpp
    http_server/services/terrain/terrains_service.cpp

    http_server/json_former/json_former.hpp
    http_server/json_former/json_former.cpp

    http_server/controllers/form_http_response.cpp
    http_server/controllers/form_http_response.hpp
)


add_executable(
    app_client

    core/main_client.cpp

    ${TERRAIN_ENGINE}
    ${GUI_ENGINE}
    ${IMAGES_ENGINE}
    ${OBJECTS_ENGINE}
    ${SCENE_ENGINE}
    ${ENTRY_ENGINE}
    ${POSTGRES_ENGINE}
    ${LOG_ENGINE}
    ${REPOSITORY}
    ${EXCEPTION_ENGINE}
    ${CONFIG_ENGINE}
    ${REDIS_ENGINE}
)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(
    unit_all_tests

    tests/main_tests.cpp
    ${TESTS}
    ${TERRAIN_ENGINE}
    ${IMAGES_ENGINE}
    ${CONFIG_ENGINE}
    ${EXCEPTIONS_ENGINE}
    ${GUI_ENGINE}
    ${LOG_ENGINE}
    ${OBJECT_TRANSFORM_ENGINE}
    ${REPOSITORY_FILES}
    ${REPOSITORY_USERS}
    ${POSTGRES_ENGINE}
    ${ENTRY_ENGINE}

    core/data_access/db_model/base_db_model.hpp

    core/data_access/data_interfaces/interface_users_db.h


)

add_executable(
    http_server

    http_server/main_http_server.cpp

    ${HTTP_SERVER}
    ${TERRAIN_ENGINE}
    ${GUI_ENGINE}
    ${IMAGES_ENGINE}
    ${SERVER_SOURCERS}
    ${LOG_ENGINE}
    ${ENTRY_ENGINE}
)


gtest_discover_tests(unit_all_tests)

#Redis configuration
find_path(HIREDIS_HEADER hiredis)
target_include_directories(app_client PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)

find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(app_client PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)

#Library dependencies
target_link_libraries(unit_all_tests Qt5::Gui Qt5::Widgets
                    -lpqxx -lpq -ljsoncpp -lpng
                     ${JSONCPP_LIBRARIES} mysqlcppconn
                     -lpthread -lboost_log -lnghttp2_asio -lboost_system -lboost_thread
                     -lssl -lcrypto -ljwt -lpng -lz
                     Drogon::Drogon
                     gtest gmock pthread)

target_link_libraries(app_client Qt5::Gui Qt5::Widgets Qt5::Network
                        ${HIREDIS_LIB} ${REDIS_PLUS_PLUS_LIB}
                        -lpqxx -lpq
                        -ljsoncpp  ${JSONCPP_LIBRARIES}
                        mysqlcppconn  -lpthread -lssl -lcrypto -ljwt -lpng -lz)

target_link_libraries(http_server Qt5::Gui Qt5::Widgets Qt5::Network
                        ${HIREDIS_LIB} ${REDIS_PLUS_PLUS_LIB}
                        -lpqxx -lpq
                        -ljsoncpp  ${JSONCPP_LIBRARIES}
                        mysqlcppconn  -lpthread -lboost_log -lnghttp2_asio -lboost_system -lboost_thread
                        -lssl -lcrypto -ljwt -lpng -lz
                        Drogon::Drogon)

