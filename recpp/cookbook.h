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

#ifndef COOKBOOK_H
#define COOKBOOK_H

#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <recipe.h>

/*
    Structure of one Cookbook:
    |
    |--Name
    |--Description
    |--Comment
    |--File Name
    |--Recipes
    |  |--Recipe 1 (cf. recipe)
    |  |--Recipe 2
    |--num Recipes
*/

class Cookbook {
private:
    QString name;
    QString description;
    QString comment;
    QString fileName;
    int numberOfRecipes;
    Recipe *recipes[];

public:
    Cookbook();
    Cookbook(QString name, QString description, QString comment,
             QString fileName);
    Cookbook(QString fileName);
    std::string getName();
    ~Cookbook();

    // write methods
    void WriteRecppToRecpp(QString fileName);
//    void WriteRecppToDB(QString fileName);
//    void WriteRecppToTxt(QString fileName);

    // Read methods
//    void ReadRecppFromRecpp(QString fileName); //void might be inappropriate
//    void ReadRecppFromDB(QString fileName); //void might be inappropriate
//    void ReadRecppFromTxt(QString fileName); //void might be inappropriate

    // add or remove recipe

};

Cookbook::Cookbook(){
    this->name = "";
    this->description = "";
    this->comment = "";
    this->fileName = "";
    this->numberOfRecipes = 0;
}

Cookbook::Cookbook(QString name, QString description, QString comment,
                   QString fileName){
    this->name = name;
    this->description = description;
    this->comment = comment;
    this->fileName = fileName;
    this->numberOfRecipes = 0;

    // if file exists, read; else write create empty cookbook file.

}

Cookbook::Cookbook(QString fileName){
    this->fileName = fileName;

    //Cookbook *tmp = new Cookbook();
}

Cookbook::~Cookbook(){
}

//void WriteRecppToRecpp(QString fileName){

//}

//void WriteRecppToDB(QString fileName){
//    sqlite3 *db;
//    int rc;
//    std::string sql = "CREATE TABLE META("
//            "";
//    // open database
//    rc = sqlite3_open(fileName, &db);
//    sqlite3_exec(db, sql, NULL, NULL, NULL);
//}

//void WriteRecppToTxt(QString fileName){

//}



#endif // COOKBOOK_H
