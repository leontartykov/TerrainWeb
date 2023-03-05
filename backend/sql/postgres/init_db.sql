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
	name varchar,
	primary key(name),
	
	last_edited date,
	rating real,
	n_rates integer,
	exhibited boolean,

	id_terrain int,
	foreign key(id_terrain) references terrain_project.terrains.terrains(id)
);

CREATE TABLE IF NOT EXISTS terrain_project.terrains.users_projs
(
	id_user int,
	foreign key(id_user) references terrain_project.users.info(id),

	proj_name varchar,
	foreign key(proj_name) references terrain_project.terrains.projects(name)
);


