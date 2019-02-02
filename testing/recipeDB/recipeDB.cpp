/*
 *  recpp - A digital cookbook for managing your recipes.
 *  Copyright (C) 2018 Matthias Weigand -- matthias.weigand[at]protonmail.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  Adapted from
 *  https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
 *
 *
 * test compile with:
 * touch test.sqlite && rm test.sqlite && g++ recipeDB.cpp -l sqlite3 && ./a.out
 */



#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;
    const char* data = "Callback function called";

    rc = sqlite3_open("test.sqlite", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    // Create SQL statement
    sql = "CREATE TABLE RECIPES(" \
          "ID INT PRIMARY  KEY       NOT NULL," \
          "NAME            TEXT      NOT NULL," \
          "COMMENT         TEXT," \
          "INGREDIENTS     TEXT," \
          // to be denotet amnt1;unit1;what1;amt2;...
          "INSTRUCTIONS    TEXT," \
          "RATING          INTEGER," \
          "DIFFICULTY      INTEGER," \
          "PREPARATIONTIME INTEGER," \
          "CUISINE         CHAR(50));";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    // Insert values into table
    sql = "INSERT INTO RECIPES (ID, NAME, COMMENT, INGREDIENTS, INSTRUCTIONS, " \
            "RATING, DIFFICULTY, PREPARATIONTIME, CUISINE)" \
          "VALUES (0, 'Recipe1', 'A comment on the recipe', '1;kg;joy;2;liter;beer'," \
            "'drink beer and have the joy', 5, 1, 10, 'Bavarian');";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Values successfully inserted into table\n");
    }


    // read values from table
    sql = "SELECT * FROM RECIPES";

    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Values successfully read from table\n");
        //fprintf(data);
    }
    sqlite3_close(db);

    return(0);
}
