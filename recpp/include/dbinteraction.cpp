#include "dbinteraction.h"
#include "cookbook.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <QDebug>
#include <vector>
#include <string>


// Constructors
dbInteraction::dbInteraction(){

}

dbInteraction::dbInteraction(const char *fileName){
    this->dbName = fileName;
}

// Destructors
dbInteraction::~dbInteraction(){

}

bool dbInteraction::dbAccessible(){
    this->rc = sqlite3_open(dbName, &db);
    if (this->rc){
        return false;
    } else {
        return true;
    }
}

std::vector<QString> dbInteraction::listCookbooks(const char *dbFile){
    std::vector<QString> cbNames;
    const char *sql;

    this->rc = sqlite3_open(dbFile, &db);
    sql = "SELECT NAME FROM COOKBOOKS";
//    sqlite3_stmt *stmt;

    if (this->rc){
        qDebug() << "Error opening database while listing Cookbooks";
    } else {
        this->rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (this->rc != SQLITE_OK){
            qDebug() << "Error opening data base with statement while listing Cookbooks";
        } else {
            while ((this->rc = sqlite3_step(stmt)) == SQLITE_ROW){
                const unsigned char *name = sqlite3_column_text(stmt, 0);
                QString qsName = getQStringFromUnsignedChar(name);
                cbNames.push_back(qsName);
            }
        }
    }

    return cbNames;
}

//TODO
Cookbook dbInteraction::loadCookbook(QString name){
    Cookbook *cb = new Cookbook;
    QString descr = "";
    QString comm = "";
    QString recipeIDs = "";
    QString fileName = "";
    int nOfRec = 0;

//    if (this->dbAccessible()){
//        this->sql = "SELECT * FROM RECIPES;";
//        return parseSqlToCookbook(this->sql);
//    }

    cb->setName(name);
    cb->setDescription(descr);
    cb->setComment(comm);

    return *cb;
}

// TODO
Recipe dbInteraction::loadRecipe(const char *dbFile, int recipeId){
    Recipe *rec = new Recipe;
    const char *sql;

    this->rc = sqlite3_open(dbFile, &db);
    sql = "SELECT ID, NAME FROM RECIPES";
//    sqlite3_stmt *stmt;


//    if (rc){
//        qDebug() << "Error opening database while listing Cookbooks";
//    } else {
//        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
//        if (rc != SQLITE_OK){
//            qDebug() << "Error opening data base with statement while listing Cookbooks";
//        } else {
//            while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
//                const unsigned char *name = sqlite3_column_text(stmt, 0);
//                QString qsName = getQStringFromUnsignedChar(name);
//                cbNames.push_back(qsName);
//            }
//        }
//    }
    return *rec;
}

void dbInteraction::initializeDatabase(){
    const char *sql;

    this->rc = sqlite3_open(this->dbName, &this->db);
    if (this->rc){
        qDebug() << "Error opening database";
    } else {
        qDebug() << "Database sucessfully opened";
    }

    // initiate table COOKBOOKS
    sql =   "CREATE TABLE COOKBOOKS(" \
            "ID          INT PRIMARY KEY NOT NULL," \
            "NAME        TEXT NOT NULL," \
            "DESCRIPTION TEXT," \
            "COMMENT     TEXT," \
            "RECIPESID   TEXT," \
            "NUMRECIPES  INT);";
    this->rc = sqlite3_exec(this->db, sql, nullptr, nullptr, &this->zErrMsg);
    if (this->rc != SQLITE_OK){
        qDebug() << "Error creating COOKBOOKS table";
    } else {
        qDebug() << "Table COOKBOOKS successfully created";
    }

    // initiate table RECIPES
    sql =   "CREATE TABLE RECIPES(" \
            "ID              INT PRIMARY KEY NOT NULL," \
            "NAME            TEXT NOT NULL," \
            "COMMENT         TEXT," \
            "NUMPORTIONS     INT," \
            "INGREDIENTS     TEXT," \
            "INSTRUCTIONS    TEXT," \
            "RATING          INT," \
            "DIFFICULTY      INT," \
            "PREPARATIONTIME INT," \
            "CUISINE         CHAR(50));";
    this->rc = sqlite3_exec(this->db, sql, nullptr, nullptr, &this->zErrMsg);
    if (this->rc != SQLITE_OK){
        qDebug() << "Error creating RECIPES table";
    } else {
        qDebug() << "Table RECIPES successfully created";
    }

    sqlite3_close(this->db);
}

void dbInteraction::createDummyRecipe(){
    const char *sql;

    this->rc = sqlite3_open(this->dbName, &this->db);

    sql = "INSERT INTO RECIPES (ID, NAME, COMMENT, INGREDIENTS, INSTRUCTIONS, " \
                "RATING, DIFFICULTY, PREPARATIONTIME, CUISINE)" \
              "VALUES (0, 'Recipe1', 'A comment on the recipe', '1;kg;joy;2;liter;beer'," \
                "'drink beer and have the joy', 5, 1, 10, 'Bavarian');";

    this->rc = sqlite3_exec(db, sql, this->callback, nullptr, &this->zErrMsg);
    if (this->rc != SQLITE_OK){
        qDebug() << "Error inserting dummy recipe";
    } else {
        qDebug() << "Dummy recipe successfully created";
    }
}


QString dbInteraction::getQStringFromUnsignedChar(const unsigned char *str){
    // cf. https://stackoverflow.com/a/12417415
    // and https://stackoverflow.com/a/17713862
    QString s;
    QString result = "";
    int lengthOfString = strlen(reinterpret_cast<const char*>(str));

    // Print String in Reverse order....
    for (int i = 0; i < lengthOfString; i++) {
        s = QString("%1").arg(str[i],0,16);

        if(s.length() == 1){
            result.append("0");
        }
        result.append(s);
    }
    return result;
}

const unsigned char* dbInteraction::getUnsignedCharFromQString(QString qstr){
    const unsigned char *str = reinterpret_cast<const unsigned char*>(qstr.data());
    return str;
}


int dbInteraction::callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

