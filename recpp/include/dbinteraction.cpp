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

// Getters
QString dbInteraction::getDbName(){
    return(this->dbName);
}

bool dbInteraction::isAccessible(){
    if (this->db.open()){
        this->db.close();
        return(true);
    } else {
        return(false);
    }
}


// Setters
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
        query.exec("CREATE TABLE COOKBOOK(" \
                   "ID          INT PRIMARY KEY NOT NULL," \
                   "NAME        TEXT NOT NULL," \
                   "DESCRIPTION TEXT," \
                   "COMMENT     TEXT," \
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
        // add dummy cookbook
        query.exec("INSERT INTO COOKBOOK (ID, NAME, DESCRIPTION, COMMENT, NUMRECIPES)" \
                   "VALUES (0, 'Recipe1', 'A description on the recipe', 'A comment on the recipe', 1);");
        qDebug() << "Error when inserting into cookbook" << query.lastError();

        // add dummy recipe
        query.exec("INSERT INTO RECIPES (ID, NAME, COMMENT, INGREDIENTS, INSTRUCTIONS, " \
                   "RATING, DIFFICULTY, PREPARATIONTIME, CUISINE)" \
                   "VALUES (0, 'Recipe1', 'A comment on the recipe', '1;kg;joy;2;liter;beer'," \
                   "'drink beer and have the joy', 5, 1, 10, 'Bavarian');");
        qDebug() << "Error when inserting into recipes" << query.lastError();

        this->db.close();
        qDebug() << "Data base closed successfully";
    } else {
        qDebug() << "Error opening data base: " << db.lastError().text();
    }
}

QSqlQueryModel * dbInteraction::getQueryModel(){

    if(this->db.open()){
        qDebug() << "Successfully opened data base for reading queryModel";

        // create the return model
        QSqlQueryModel * model = new QSqlQueryModel();

        // initialize the query
        QSqlQuery * query = new QSqlQuery(this->db);
        query->prepare("select * from COOKBOOK;");
        query->exec();

        model->setQuery(*query);
        this->db.close();
        return(model);
    } else {
        qDebug() << "Error opening data base for reading queryModel";
        return(nullptr);
    }
}


