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

#include "ingredients.h"

// Constructors
Ingredients::Ingredients()
{

}

// Destructors
Ingredients::~Ingredients(){

}

// Getters
std::vector<float> Ingredients::getAmounts(){
    return this->amounts;
}

std::vector<QString> Ingredients::getIngredients(){
    return this->ingredients;
}

// Setters
void Ingredients::addIngredient(float a, QString i){
    this->amounts.push_back(a);
    this->ingredients.push_back(i);
}
