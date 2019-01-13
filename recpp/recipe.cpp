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

#include <recipe.h>

// Constructors
Recipe::Recipe(){

}

// Destructors
Recipe::~Recipe(){

}

// Getters
QString Recipe::getName(){
    return this->name;
}

QString Recipe::getDescription(){
    return this->description;
}

QString Recipe::getComment(){
    return this->comment;
}

int Recipe::getPortions(){
    return this->portions;
}

Ingredients Recipe::getIngredients(){
    return this->ingredients;
}

QString Recipe::getInstructions(){
    return this->instructions;
}

int Recipe::getRating(){
    return this->rating;
}

int Recipe::getDifficulty(){
    return this->difficulty;
}

int Recipe::getPreparationTime(){
    return this->preparationTime;
}

QString Recipe::getCuisine(){
    return this->cuisine;
}



