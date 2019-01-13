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

#include "recpp.h"
#include "ui_recpp.h"
#include <QtDebug>
#include <cookbook.h>

static Cookbook *cookbook;

recpp::recpp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::recpp)
{
    ui->setupUi(this);
}

recpp::~recpp()
{
    delete ui;
}

void recpp::on_actionExit_triggered()
{
    QApplication::quit();
}

void recpp::on_actionNew_Cookbook_triggered()
{
    QString name = "";
    QString description = "";
    QString comment = "";
    QString fileName = QFileDialog::getSaveFileName(this, "Create Cookbook",
                                                    "", tr("Cookbook *.recpp, *.rectxt, *.recdb"));

    // check and append correct file ending if needed
    QFileInfo fi(fileName);
    if (fi.suffix() != "recpp") fileName += ".recpp";
    qDebug() << fileName << "\n";

    Cookbook *cookbook = new Cookbook(name, description, comment, fileName);
}

void recpp::on_actionOpen_Cookbook_triggered()
{

}