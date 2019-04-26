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

#ifndef DBINTERACTION_H
#define DBINTERACTION_H

#include <QString>
#include <QtSql>
#include "cookbook.h"

/*
    The Structure of a recpp sqlite the Following:

    TABLE META
        COLUMNS |
                |--CDATE
                |--NAME
                |--DESCRIPTION
                |--VERSION

    TABLE COOKBOOK
        COLUMNS |
                |--ID
                |--NAME
                |--DESCRIPTION
                |--COMMENT
                |--RECIPEID
                |--NUMRECIPES

    TABLE RECIPES
        COLUMNS |
                |--ID
                |--NAME
                |--COMMENT
                |--NUMPORTIONS
                |--INGREDIENTS
                |--INSTRUCTIONS
                |--RATING
                |--DIFFICULTY
                |--PREPARATIONTIME
                |--CUISINE
*/

class dbInteraction
{
private:
    QString dbName;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");



public:
//    dbInteraction();
    dbInteraction(QString dbname);
    ~dbInteraction();

    // Getters
    QString getDbName();
    QSqlQueryModel * getQueryModel();
    bool isAccessible();

    // Setters
    void addRecipe(QString name, QString comment, int numPortions,
                   QString ingredients, QString instructions, int rating,
                   int preparationTime, int difficulty, QString cuisine);

    // initialize Database
    void initializeDatabase();

    // fill database with dummy recipe
    void createDummyRecipe();

    // reload data base after each interaction with DB


};

#endif // DBINTERACTION_H
