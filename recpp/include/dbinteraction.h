#ifndef DBINTERACTION_H
#define DBINTERACTION_H

#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "cookbook.h"

/*
    The Structure of a recpp sqlite the Following:

    TABLE COOKBOOKS
        COLUMNS |
                |--ID
                |--NAME
                |--DESCRIPTION
                |--COMMENT
                |--RECIPESID
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
    const char *dbName;
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;
    sqlite3_stmt *stmt;

public:
    dbInteraction();
    ~dbInteraction();

    // Getters
    QString getDbName();
    bool dbAccessible();
    Cookbook parseSqlToCookbook(const char *sqlReturn);


    // setters

    // Parse Database
    std::vector<QString> listCookbooks(const char *dbFile);
    Cookbook loadCookbook(QString name);
    Recipe loadRecipe(const char *dbFile, int recipeId);
    // todo: could help debugging
    //std::vector<Cookbook> loadAllCookbooks();
    //std::vector<Recipe> loadAllRecipes();





    // initialize Database

    void initializeDatabase(const char *fileName);

    // conversion tools
    QString getQStringFromUnsignedChar(const unsigned char *str);
    const unsigned char* getUnsignedCharFromQString(QString qstr);

};

#endif // DBINTERACTION_H
