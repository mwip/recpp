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

    // initialize Database
    void initializeDatabase();

    // fill database with dummy recipe
    void createDummyRecipe();

};

#endif // DBINTERACTION_H
