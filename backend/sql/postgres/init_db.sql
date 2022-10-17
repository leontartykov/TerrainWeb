CREATE DATABASE terrain_project;
CREATE SCHEMA terrain_project.users;

CREATE TABLE IF NOT EXISTS terrain_project.users.passwords
(
	id int,
	login varchar,
	primary key(id, login),
	
	password varchar,
	perm_level int,
	blocked boolean,
	deleted boolean
);

INSERT INTO terrain_project.users.passwords values
(0, 'admin', 'admin', 0, false, false);

CREATE TABLE IF NOT EXISTS terrain_project.terrains.terrain
(
	id int primary key,
	name varchar primary key,
	last_edited date,

	project_id int,
	foreign key(project_id) references terrain_project.terrains.projects(id)
);

CREATE TABLE IF NOT EXISTS terrain_project.terrains.terrains_users
(
	id_user int,
	foreign key(id_user) references terrain_project.users.passwords(id),

	id_terrain int,
	foreign key(id_terrain) references terrain_project.terrains.terrain(id)
);

CREATE TABLE IF NOT EXISTS terrain_project.terrains.projects
(
	id int primary key;
	width int,
	height int,
	scale double precision,
	octaves int,
	gain double precision,
	lacunarity double precision,
	seed int,
	frequency double precision,
	angle_x int,
	angle_y int,
	angle_z int
);
