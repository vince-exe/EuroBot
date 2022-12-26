CREATE DATABASE testDB;

USE testDB;

CREATE TABLE users (
	ID varchar(30) NOT NULL PRIMARY KEY,
    username varchar(25),
    coins int
);

CREATE TABLE bet (
	ID int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    userID varchar(30) NOT NULL,
    coins int NOT NULL,
    state BIT(1) NOT NULL,
    date_ DATE NOT NULL,
    
    FOREIGN KEY (userID) REFERENCES users(ID)
);