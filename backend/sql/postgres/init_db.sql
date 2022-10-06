CREATE DATABASE IF NOT EXISTS Users;

CREATE TABLE IF NOT EXISTS Users.passwords
(
	login varchar primary key;
	password varchar;
	blocked boolean;
	deleted boolean;
);

INSERT INTO Users.passwords values
('admin', 'admin', false, false);
