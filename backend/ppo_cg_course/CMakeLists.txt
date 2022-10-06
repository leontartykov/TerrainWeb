cmake_minimum_required(VERSION 3.5)

project(ppo_cg_course LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++14 -DQT_NO_VERSION_TAGGING")

include(GoogleTest)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Network COMPONENTS QtNetwork REQUIRED)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR your_path_to_mysql_connectorcpp)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/cppconn)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)


add_executable(
    core_files

    core/main.cpp

    core/geometry/point/point_base.h
    core/geometry/point/point_3d.h
    core/geometry/point/point_3d.hpp
    core/geometry/point/point_3d.cpp

    core/geometry/point/point_2d.h
    core/geometry/point/point_2d.hpp
    core/geometry/point/point_2d.cpp

    core/geometry/vector/vector_3d.h
    core/geometry/vector/vector_3d.hpp

    core/heightmap/base_noise.h
    core/heightmap/perlin_noise/perlin_original.h
    core/heightmap/perlin_noise/perlin_original.hpp
    core/heightmap/perlin_noise/perlin_original.cpp

    core/heightmap/perlin_noise/perlin_noise_struct.h

    core/object/object_base.h
    core/object/terrain/base_terrain.h
    core/object/terrain/terrain.h
    core/object/terrain/terrain.hpp
    core/object/terrain/terrain.cpp

    core/object/terrain/terrain_struct.h

    core/object/terrain/terrain_facade/terrain_facade.h
    core/object/terrain/terrain_facade/terrain_facade.cpp

    core/scene/scene_commands/scene_command_base.h
    core/scene/scene_commands/scene_command_base.cpp
    core/scene/scene_commands/scene_commands.cpp
    core/scene/scene_commands/scene_commands.h

    core/scene/scene_facade/scene_facade.h
    core/scene/scene_facade/scene_facade.cpp

    core/scene/scene.h
    core/scene/scene.cpp

    core/scene/scene_struct.h

    core/object/terrain/terrain_commands/terrain_commands.h
    core/object/terrain/terrain_commands/terrain_commands.cpp

    core/object/terrain/terrain_struct.h

    core/object/light/light.h
    core/object/light/light.cpp

    core/invisible/zbuffer/zbuffer_base.h
    core/invisible/zbuffer/zbuffer.h
    core/invisible/zbuffer/zbuffer.hpp
    core/invisible/zbuffer/zbuffer.cpp

    core/geometry/triangle/triangle_3d.h
    core/geometry/triangle/triangle_3d.hpp
    core/geometry/triangle/triangle_3d.cpp

    core/geometry/plane/plane.h
    core/geometry/plane/plane.cpp

    #core/data_access/data_access_base.h
    core/data_access/data_access_file/data_access_file_base.h
    core/data_access/data_access_file/data_access_file.h
    core/data_access/data_access_file/data_access_file.hpp

    core/data_access/data_access_image/data_access_image_base.h
    core/data_access/data_access_image/data_access_image_bmp.h
    core/data_access/data_access_image/data_access_image_bmp.hpp
    core/data_access/data_access_image/data_access_image_bmp.cpp
    core/data_access/data_access_image/bmp_structure.h

    core/data_access/users/users_struct.h
    core/data_access/users/base_user.h
    core/data_access/users/base_user.cpp

    core/data_access/users/user/users.h
    core/data_access/users/user/users.cpp

    core/data_access/users/admin/admin.h
    core/data_access/users/admin/admin.cpp

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

    core/gui/main_window.cpp
    core/gui/main_window.h
    core/gui/mainwindow.ui
    #core/gui/ui_mainwindow.h

    core/transform/transform.h
    core/transform/transform.cpp

    core/log_app/log_app.h
    core/log_app/log_app.cpp
    core/log_app/log_structs.h

    core/exceptions/base_error.h
    core/exceptions/errors.h

    core/config/config_struct.h
    core/config/config.h
    core/config/config.cpp

    server/server.h
    server/server.cpp
    server/async_con.h
    server/async_con.cpp
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
  unit_tests/tests_point_3d.cpp
  unit_tests/tests_vector_3d.cpp
  unit_tests/tests_perlin_noise.cpp
  unit_tests/tests_zbuffer.cpp
  unit_tests/tests_plane.cpp
  unit_tests/tests_file.cpp
  unit_tests/tests_image.cpp
  unit_tests/tests_users.cpp

  core/geometry/point/point_base.h
  core/geometry/point/point_3d.h
  core/geometry/point/point_3d.hpp
  core/geometry/point/point_3d.cpp

  core/geometry/point/point_2d.h
  core/geometry/point/point_2d.hpp
  core/geometry/point/point_2d.cpp

  core/geometry/vector/vector_3d.h
  core/geometry/vector/vector_3d.hpp

  core/heightmap/base_noise.h
  core/heightmap/perlin_noise/perlin_original.h
  core/heightmap/perlin_noise/perlin_original.hpp
  core/heightmap/perlin_noise/perlin_original.cpp

  core/heightmap/perlin_noise/perlin_noise_struct.h

  core/object/object_base.h
  core/object/terrain/base_terrain.h
  core/object/terrain/terrain.h
  core/object/terrain/terrain.hpp
  core/object/terrain/terrain.cpp

  core/object/terrain/terrain_facade/terrain_facade.h
  core/object/terrain/terrain_facade/terrain_facade.cpp


  core/object/terrain/terrain_commands/terrain_commands.h
  core/object/terrain/terrain_commands/terrain_commands.cpp

  core/scene/scene_commands/scene_command_base.h
  core/scene/scene_commands/scene_command_base.cpp
  core/scene/scene_commands/scene_commands.cpp
  core/scene/scene_commands/scene_commands.h

  core/scene/scene_facade/scene_facade.h
  core/scene/scene_facade/scene_facade.cpp

  core/scene/scene.h
  core/scene/scene.cpp

  core/scene/scene_struct.h


  core/object/light/light.h
  core/object/light/light.cpp

  core/invisible/zbuffer/zbuffer_base.h
  core/invisible/zbuffer/zbuffer.h
  core/invisible/zbuffer/zbuffer.hpp
  core/invisible/zbuffer/zbuffer.cpp

  core/geometry/triangle/triangle_3d.h
  core/geometry/triangle/triangle_3d.hpp
  core/geometry/triangle/triangle_3d.cpp

  core/geometry/plane/plane.h
  core/geometry/plane/plane.cpp

  #core/data_access/data_access_base.h
  core/data_access/data_access_file/data_access_file_base.h
  core/data_access/data_access_file/data_access_file.h
  core/data_access/data_access_file/data_access_file.hpp

  core/data_access/data_access_image/data_access_image_base.h
  core/data_access/data_access_image/data_access_image_bmp.h
  core/data_access/data_access_image/data_access_image_bmp.hpp
  core/data_access/data_access_image/data_access_image_bmp.cpp
  core/data_access/data_access_image/bmp_structure.h

  core/data_access/users/users_struct.h
  core/data_access/users/base_user.h
  core/data_access/users/base_user.cpp

  core/data_access/users/user/users.h
  core/data_access/users/user/users.cpp

  core/data_access/users/admin/admin.h
  core/data_access/users/admin/admin.cpp

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

  core/gui/main_window.cpp
  core/gui/main_window.h
  core/gui/mainwindow.ui
  #core/gui/ui_mainwindow.h

  core/transform/transform.h
  core/transform/transform.cpp

  core/log_app/log_app.h
  core/log_app/log_app.cpp
  core/log_app/log_structs.h

  core/exceptions/base_error.h
  core/exceptions/errors.h

  core/config/config_struct.h
  core/config/config.h
  core/config/config.cpp
)



gtest_discover_tests(unit_all_tests)

target_link_libraries(unit_all_tests Qt5::Gui Qt5::Widgets -lpqxx -lpq -ljsoncpp ${JSONCPP_LIBRARIES} mysqlcppconn
                                gtest gtest_main)
target_link_libraries(core_files Qt5::Gui Qt5::Widgets Qt5::Network -lpqxx -lpq -ljsoncpp ${JSONCPP_LIBRARIES} mysqlcppconn)


