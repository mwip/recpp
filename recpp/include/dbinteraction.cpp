/*
    recpp - A digital cookbook for managing your recipes.
    Copyright (C) 2018 Matthias Weigand -- matthias.weigand[at]protonmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

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
void dbInteraction::addRecipe(QString name, QString comment, int numPortions,
                              QString ingredients, QString instructions,
                              int rating, int preparationTime, QString cuisine){
    QSqlQuery query;

    if (this->db.open()){
        query.prepare("INSERT INTO RECIPES (NAME, COMMENT, NUMPORTIONS, "
                      "INGREDIENTS, INSTRUCTIONS, RATING, PREPARATIONTIME, "
                      "CUISINE) "
                      "VALUES (:name, :comment, :numportions, :ingredients, "
                      ":instructions, :rating, :preparationtime, :cuisine");
        query.bindValue(":name", name);
        query.bindValue(":comment", comment);
        query.bindValue(":numportions", numPortions);
        query.bindValue(":ingredients", ingredients);
        query.bindValue(":instructions", instructions);
        query.bindValue(":rating", rating);
        query.bindValue(":preparationtime", preparationTime);
        query.bindValue(":cuisine", cuisine);
        query.exec();

        this->db.close();
        qDebug() << "Sucessfully added recipe: " << name;

    } else {
        qDebug() << "Error writing recipe " << name << " to data base";
    }



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


