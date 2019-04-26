#include "newrecipe.h"
#include "ui_newrecipe.h"

newRecipe::newRecipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newRecipe)
{
    ui->setupUi(this);
}

newRecipe::~newRecipe()
{
    delete ui;
}

void newRecipe::on_buttonBox_accepted()
{

}
