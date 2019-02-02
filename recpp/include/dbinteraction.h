#ifndef DBINTERACTION_H
#define DBINTERACTION_H

#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "cookbook.h"


class dbInteraction
{
private:
    QString dbName;
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;

//    static int callback(void *NotUsed, int argc, char **argv, char **azColName){
//       int i;
//       for(i = 0; i<argc; i++) {
//          printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//       }
//       printf("\n");
//       return 0;
//    }

public:
    dbInteraction();
    ~dbInteraction();

    // Getters
    QString getDbName();
    bool dbAccessible();
    Cookbook parseSqlToCookbook(QString sqlReturn);
    Cookbook loadCookbook();


};

#endif // DBINTERACTION_H
