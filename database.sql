CREATE DATABASE testDB;

USE testDB;

CREATE TABLE users (
	ID varchar(30) NOT NULL PRIMARY KEY,
    username varchar(25),
    coins int
);