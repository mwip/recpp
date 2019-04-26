#ifndef NEWRECIPE_H
#define NEWRECIPE_H

#include <QDialog>

namespace Ui {
class newRecipe;
}

class newRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit newRecipe(QWidget *parent = nullptr);
    ~newRecipe();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::newRecipe *ui;
};

#endif // NEWRECIPE_H
