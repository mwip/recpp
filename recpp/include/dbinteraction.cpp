#include "dbinteraction.h"
#include "cookbook.h"
#include <QtSql>
#include <QDebug>
#include <vector>
#include <string>


// Constructors
//dbInteraction::dbInteraction(){
//}

dbInteraction::dbInteraction(QString dbname){
    this->dbName = dbname;
    this->db.setDatabaseName(this->dbName);
}

// Destructors
dbInteraction::~dbInteraction(){

}

void dbInteraction::initializeDatabase(){
    // initialize a database from scratch
    // creates required tables

    // open the data base
    if(this->db.open()){
        qDebug() << "Data base opened successfully";

        QSqlQuery query;

        // create three tables
        // initiate table META
        query.exec("CREATE TABLE META(" \
                        "CDATE        INT PRIMARY KEY NOT NULL," \
                        "NAME         TEXT NOT NULL," \
                        "DESCRIPTION  TEXT," \
                        "VERSION      TEXT);");

        // initiate table COOKBOOKS
        query.exec("CREATE TABLE COOKBOOKS(" \
                   "ID          INT PRIMARY KEY NOT NULL," \
                   "NAME        TEXT NOT NULL," \
                   "DESCRIPTION TEXT," \
                   "COMMENT     TEXT," \
                   "RECIPESID   TEXT," \
                   "NUMRECIPES  INT);");

        // initiate table RECIPES
        query.exec("CREATE TABLE RECIPES(" \
                   "ID              INT PRIMARY KEY NOT NULL," \
                   "NAME            TEXT NOT NULL," \
                   "COMMENT         TEXT," \
                   "NUMPORTIONS     INT," \
                   "INGREDIENTS     TEXT," \
                   "INSTRUCTIONS    TEXT," \
                   "RATING          INT," \
                   "DIFFICULTY      INT," \
                   "PREPARATIONTIME INT," \
                   "CUISINE         CHAR(50));");

        //close the database
        this->db.close();
        qDebug() << "Data base closed successfully";
    } else {
        qDebug() << "Error opening data base: " << db.lastError().text();
    }
}

void dbInteraction::createDummyRecipe(){
    // creates a dummy recipe within the cookbook

    // open the data base
    if(this->db.open()){
        qDebug() << "Data base opened successfully";

        QSqlQuery query;

        query.exec("INSERT INTO RECIPES (ID, NAME, COMMENT, INGREDIENTS, INSTRUCTIONS, " \
                   "RATING, DIFFICULTY, PREPARATIONTIME, CUISINE)" \
                   "VALUES (0, 'Recipe1', 'A comment on the recipe', '1;kg;joy;2;liter;beer'," \
                   "'drink beer and have the joy', 5, 1, 10, 'Bavarian');");

        this->db.close();
        qDebug() << "Data base closed successfully";
    } else {
        qDebug() << "Error opening data base: " << db.lastError().text();
    }
}

