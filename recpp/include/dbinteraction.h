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
    char *zErrMsg = nullptr;
    int rc;
    sqlite3_stmt *stmt;

public:
    dbInteraction();
    dbInteraction(const char *fileName);
    ~dbInteraction();

    // Getters
    QString getDbName();
    bool dbAccessible();
    Cookbook parseSqlToCookbook(const char *sqlReturn);


    // setters
    void inputSqlToCookbook(const char *sqlQuery);

    // Parse Database
    std::vector<QString> listCookbooks(const char *dbFile);
    Cookbook loadCookbook(QString name);
    Recipe loadRecipe(const char *dbFile, int recipeId);
    // todo: could help debugging
    //std::vector<Cookbook> loadAllCookbooks();
    //std::vector<Recipe> loadAllRecipes();





    // initialize Database
    void initializeDatabase();

    // fill database with dummy recipe
    void createDummyRecipe();

    // conversion tools
    QString getQStringFromUnsignedChar(const unsigned char *str);
    const unsigned char* getUnsignedCharFromQString(QString qstr);

    // callback
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

};

#endif // DBINTERACTION_H
