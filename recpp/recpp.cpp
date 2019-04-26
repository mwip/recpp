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
#include "ui_newrecipe.h"
#include "include/dbinteraction.h"
#include "cookbook.h"
#include "newrecipe.h"
#include <QtDebug>
#include <QDialog>
#include <QMessageBox>


static Cookbook *cookbook = new Cookbook();

recpp::recpp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::recpp)
{
    ui->setupUi(this);
    ui->labelCurrentCookBook->setText("No cookbook chosen yet.");

}

recpp::~recpp()
{
    delete ui;
}

// Menu items

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

    // display the current data base name on screen
    ui->labelCurrentCookBook->setText(cookbook->getFileName());
    // activate load cookbook button
    ui->buttonLoadCookbook->setEnabled(true);

}

void recpp::on_actionOpen_Cookbook_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Cookbook", "",
                                                    tr("Cookbook *.recpp, *.rectxt, *.recdb"));

    if (fileName != ""){
        cookbook->loadFromFile(fileName);

        // display the current data base name on screen
        ui->labelCurrentCookBook->setText(cookbook->getFileName());
        // activate load cookbook button
        ui->buttonLoadCookbook->setEnabled(true);
    }

}

void recpp::on_actionAbout_recpp_triggered()
{
    QDialog *about = new QDialog;
    Ui::About abt;
    abt.setupUi(about);
    about->show();
}

void recpp::on_actionCreate_Dummy_Cookbook_triggered()
{
    qDebug() << "Creating new dummy recipe";
    QString fileName = QFileDialog::getSaveFileName(this, "Create Cookbook", "",
                                                    tr("Cookbook *.recpp, *.rectxt, *.recdb"));
    if (fileName != ""){
        dbInteraction *dbi = new dbInteraction(fileName);
        dbi->initializeDatabase();
        dbi->createDummyRecipe();

        cookbook->loadFromFile(fileName);

        // display the current data base name on screen
        ui->labelCurrentCookBook->setText(cookbook->getFileName());
        // activate load cookbook button
        ui->buttonLoadCookbook->setEnabled(true);
    }
}

void recpp::on_actionAdd_Recipe_triggered()
{
    // check whether a cookbook was loaded
    QString dbname = ui->labelCurrentCookBook->text();

    if (dbname != "No cookbook chosen yet."){
        // if a cookbook was loaded procede with new widget
        rcp = new newRecipe(this); // https://invidio.us/watch?v=wUH_gu2HdQE
        rcp->show();
//        rcp->show();
    } else {
        // if no cookbook was loaded yet, throw a warning
        QMessageBox::warning(this, "No Cookbook",
                             "Please load a cookbook first.");
    }
}



// Push buttons
void recpp::on_buttonOpenCookbook_clicked()
{
    // same as recpp::on_actionOpen_Cookbook_triggered()
    QString fileName = QFileDialog::getOpenFileName(this, "Open Cookbook", "",
                                                    tr("Cookbook *.recpp, *.rectxt, *.recdb"));
    if (fileName != ""){
        cookbook->loadFromFile(fileName);

        // display the current data base name on screen
        ui->labelCurrentCookBook->setText(cookbook->getFileName());
        // activate load cookbook button
        ui->buttonLoadCookbook->setEnabled(true);
    }

}

void recpp::on_buttonLoadCookbook_clicked()
{
    QString dbFile = cookbook->getFileName();
    dbInteraction * db = new dbInteraction(dbFile);

    QSqlQueryModel * model = db->getQueryModel();

    ui->tableView->setModel(model);
    ui->tableView->show();
}




