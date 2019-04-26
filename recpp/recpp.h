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

#ifndef RECPP_H
#define RECPP_H

#include <QMainWindow>
#include <QFileDialog>
#include "newrecipe.h"


namespace Ui {
class recpp;
}

class recpp : public QMainWindow
{
    Q_OBJECT

public:
    explicit recpp(QWidget *parent = nullptr);
    ~recpp();

private slots:
    void on_actionExit_triggered();

    void on_actionNew_Cookbook_triggered();

    void on_actionOpen_Cookbook_triggered();

    void on_actionAbout_recpp_triggered();

    void on_actionCreate_Dummy_Cookbook_triggered();

    void on_buttonOpenCookbook_clicked();

    void on_buttonLoadCookbook_clicked();

    void on_actionAdd_Recipe_triggered();

private:
    Ui::recpp *ui;
    newRecipe *rcp; // https://invidio.us/watch?v=wUH_gu2HdQE
};

#endif // RECPP_H
