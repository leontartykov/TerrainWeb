#include "postgres_terrains.h"

void TerrainProjectsPostgres::set_psql_connection(std::shared_ptr<pqxx::connection> &conn_psql){
    __conn_psql = conn_psql;
}

void TerrainProjectsPostgres::set_terrain_params(std::string &project_name, terrain_t &terrain_params){
    pqxx::work worker(*__conn_psql);
    std::string query = "UPDATE terrain_project.terrains.terrain SET ('" + \
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
                         "WHERE terrain_project.terrains.terrain = " + project_name + "';'";
    worker.exec(query);
    worker.commit();
}

void TerrainProjectsPostgres::get_project_terrain()
{
    pqxx::work worker(*__conn_psql);
    std::string query = "SELECT * FROM terrain_project.terrains.terrain";
    worker.exec(query);
}
