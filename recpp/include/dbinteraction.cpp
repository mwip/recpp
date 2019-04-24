#include "dbinteraction.h"
#include "cookbook.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <sqlite3.h>
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

//bool dbInteraction::dbAccessible(){

//    if (this->rc){
//        return false;
//    } else {
//        return true;
//    }
//}

//std::vector<QString> dbInteraction::listCookbooks(QString dbname){
//    std::vector<QString> cbNames;
//    const char *sql;

//    this->rc = sqlite3_open(dbFile, &db);
//    sql = "SELECT NAME FROM COOKBOOKS";
//    sqlite3_stmt *stmt;

//    if (this->rc){
//        qDebug() << "Error opening database while listing Cookbooks";
//    } else {
//        this->rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
//        if (this->rc != SQLITE_OK){
//            qDebug() << "Error opening data base with statement while listing Cookbooks";
//        } else {
//            while ((this->rc = sqlite3_step(stmt)) == SQLITE_ROW){
//                const unsigned char *name = sqlite3_column_text(stmt, 0);
//                QString qsName = getQStringFromUnsignedChar(name);
//                cbNames.push_back(qsName);
//            }
//        }
//    }

//    return cbNames;
//}

//TODO
//Cookbook dbInteraction::loadCookbook(QString name){
//    Cookbook *cb = new Cookbook;
//    QString descr = "";
//    QString comm = "";
//    QString recipeIDs = "";
//    QString fileName = "";
//    int nOfRec = 0;

////    if (this->dbAccessible()){
////        this->sql = "SELECT * FROM RECIPES;";
////        return parseSqlToCookbook(this->sql);
////    }

//    cb->setName(name);
//    cb->setDescription(descr);
//    cb->setComment(comm);

//    return *cb;
//}

// TODO
//Recipe dbInteraction::loadRecipe(const char *dbFile, int recipeId){

//}

void dbInteraction::initializeDatabase(){
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

