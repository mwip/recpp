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


#ifndef NEWRECIPE_H
#define NEWRECIPE_H

#include "cookbook.h"
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class newRecipe;
}

class newRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit newRecipe(QWidget *parent = nullptr, Cookbook *cookbook = nullptr);
    ~newRecipe();

private slots:

    void on_pushButton_addIngredient_clicked();

    void on_pushButton_removeIngredient_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

    void addRecipeToCookbook();

private:
    Ui::newRecipe *ui;
    Cookbook cookbook;
};

#endif // NEWRECIPE_H
