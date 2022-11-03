CREATE DATABASE terrain_project;
CREATE SCHEMA terrain_project.users;

CREATE TABLE IF NOT EXISTS terrain_project.users.info
(
	id int,
	primary key(id),
	
	login varchar,
	password varchar,
	perm_level int,
	blocked boolean,
	deleted boolean
);

INSERT INTO terrain_project.users.info values
(0, 'admin', 'admin', 0, false, false);

CREATE SCHEMA TERRAINS;

CREATE TABLE IF NOT EXISTS terrain_project.terrains.terrains
(
	id int,
	primary key(id),
	
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

CREATE TABLE IF NOT EXISTS terrain_project.terrains.projects
(
	id int,
	primary key(id),
	
	name varchar,
	last_edited date,

	id_terrain int,
	foreign key(id_terrain) references terrain_project.terrains.terrains(id)
);

CREATE TABLE IF NOT EXISTS terrain_project.terrains.terrains_users
(
	id_user int,
	foreign key(id_user) references terrain_project.users.info(id),

	id_terrain int,
	foreign key(id_terrain) references terrain_project.terrains.projects(id)
);
