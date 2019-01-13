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

#include <cookbook.h>

// Constructors
Cookbook::Cookbook(){
    this->name = "";
    this->description = "";
    this->comment = "";
    this->fileName = "default.recpp";
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

// Destructors
Cookbook::~Cookbook(){
}

// Getters
QString Cookbook::getName(){
    return this->name;
}

QString Cookbook::getDescription(){
    return this->description;
}

QString Cookbook::getComment(){
    return this->comment;
}

QString Cookbook::getFileName(){
    return this->fileName;
}

int Cookbook::getNumOfRecipes(){
    return this->numberOfRecipes;
}

// Setters
void Cookbook::setName(QString n){
    this->name = n;
}

void Cookbook::setDescription(QString d){
    this->description = d;
}

void Cookbook::setComment(QString c){
    this->comment = c;
}

void Cookbook::setFileName(QString f){
    this->fileName = f;
}

void Cookbook::updateNumberOfRecipes(){
    this->numberOfRecipes = int(recipes.size());
}


//void WriteRecppToRecpp(QString fileName){
//
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

