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
#include <recipe.h>
#include <vector>

/*
    Structure of one Cookbook:
    |
    |--Name
    |--Description
    |--Comment
    |--File Name
    |--Recipes
    |  |--Recipe 1 (cf. recipe, indicated by ID, referenced to table RECIPES)
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
    std::vector<Recipe*> recipes;

public:
    // Constructors / Destructors
    Cookbook();
    Cookbook(QString name, QString description, QString comment,
             QString fileName);
    Cookbook(QString fileName);
    ~Cookbook();

    // Getters
    QString getName();
    QString getDescription();
    QString getComment();
    QString getFileName();
    int getNumOfRecipes();

    // Setters
    void setName(QString n);
    void setDescription(QString d);
    void setComment(QString c);
    void setFileName(QString f);
    void setNumberOfRecipes(int n);
    void updateNumberOfRecipes();

    // load functions
    void loadFromFile(QString fileName);

    // Read methods
//    void ReadRecppFromRecpp(QString fileName); //void might be inappropriate
//    void ReadRecppFromDB(QString fileName); //void might be inappropriate
//    void ReadRecppFromTxt(QString fileName); //void might be inappropriate


    // write methods
//    void WriteRecppToRecpp(QString fileName);
//    void WriteRecppToDB(QString fileName);
//    void WriteRecppToTxt(QString fileName);


    // add or remove recipe

};




#endif // COOKBOOK_H
