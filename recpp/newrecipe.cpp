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


#include "newrecipe.h"
#include "ui_newrecipe.h"
#include "include/dbinteraction.h"
#include "cookbook.h"
#include <QDebug>
#include <QMessageBox>
#include <QAbstractButton>

newRecipe::newRecipe(QWidget *parent, Cookbook *cookbook) :
    QDialog(parent),
    ui(new Ui::newRecipe)
{
    ui->setupUi(this);
    this->cookbook = *cookbook;
}

newRecipe::~newRecipe()
{
    delete ui;
}

//void newRecipe::on_buttonBox_accepted()
//{

//}

//void newRecipe::on_buttonBox_rejected()
//{


//}


void newRecipe::on_pushButton_addIngredient_clicked()
{
    int nrows = ui->tableWidget_ingredients_2->rowCount();
    ui->tableWidget_ingredients_2->insertRow(nrows);
}

void newRecipe::on_pushButton_removeIngredient_clicked()
{
    QModelIndexList idx = ui->
            tableWidget_ingredients_2->
            selectionModel()->
            selectedRows();

    int countRow = idx.count();

    if (countRow == 0 ){
        int nrows =ui->tableWidget_ingredients_2->rowCount();
        ui->tableWidget_ingredients_2->removeRow(nrows - 1);
    } else {
        for (int i = countRow; i > 0; i--){
            ui->tableWidget_ingredients_2->removeRow(idx.at(i-1).row());
        }
    }

}


void newRecipe::on_buttonBox_clicked(QAbstractButton *button)
{
    // convert from abstract to standard button
    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);

    if (stdButton == QDialogButtonBox::Discard){
        QMessageBox::StandardButton btn;
        btn = QMessageBox::question(this, "Really close?", "Do you want to close without saving?",
                                    QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
        if (btn == QMessageBox::Yes){
            this->close();
        }
    } else if (stdButton == QDialogButtonBox::Save){
        // add recipe to the database and reload the table
        this->addRecipeToCookbook();
        this->close();
    }
}

void newRecipe::addRecipeToCookbook(){
    QString name = ui->lineEdit_Name_2->text();
    QString comment = ui->lineEdit_Comment_2->text();
    int numportions = ui->spinBox_nPortions_2->value();
    QString ingredients = "1 dummy Ingredient";// TODO ingredients
    QString instructions = ui->plainTextEdit_Instructions_2->toPlainText();
    int rating = ui->spinBox_Rating_2->value();
    int preptime = ui->spinBox_preptime->value();
    int difficulty = ui->spinBox_Difficulty_2->value();
    QString cuisine = ui->lineEdit_Cuisine->text();

    dbInteraction * db = new dbInteraction(this->cookbook.getFileName());

    db->addRecipe(name, comment, numportions, ingredients, instructions, rating,
                  preptime, difficulty, cuisine);
}
