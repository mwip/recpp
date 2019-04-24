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
#include "ui_about.h"
#include "include/dbinteraction.h"
#include <QtDebug>
#include <QDialog>
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
    QString fileName = QFileDialog::getSaveFileName(this, "Create Cookbook", "",
                                                    tr("Cookbook *.recpp, *.rectxt, *.recdb"));

    // check and append correct file ending if needed
    QFileInfo fi(fileName);
    if (fi.suffix() != "recpp" | fi.suffix() != "recdb" |
            fi.suffix() != "rectxt") {
        fileName += ".recpp";
    }

    // initialize the data base
    dbInteraction *dbi = new dbInteraction(fileName);
    dbi->initializeDatabase();

//    Cookbook *cookbook = new Cookbook(name, description, comment, fileName);
}

void recpp::on_actionOpen_Cookbook_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Cookbook", "",
                                                    tr("Cookbook *.recpp, *.rectxt, *.recdb"));
    Cookbook *cookbook = new Cookbook;
    cookbook->loadFromFile(fileName);

}

void recpp::on_actionAbout_recpp_triggered()
{
    QDialog *about = new QDialog;
    Ui::About ui;
    ui.setupUi(about);
    about->show();
}

// Dummy Cookbook functions //

void recpp::on_actionCreate_Dummy_Cookbook_triggered()
{
    qDebug() << "Creating new dummy recipe";
    QString fileName = QFileDialog::getSaveFileName(this, "Create Cookbook", "",
                                                    tr("Cookbook *.recpp, *.rectxt, *.recdb"));
//    const char *fn = fileName.toLocal8Bit().data();

    dbInteraction *dbi = new dbInteraction(fileName);
    dbi->initializeDatabase();
    dbi->createDummyRecipe();

}

// END Dummy Cookbook functions //
