#include "MenuUI.h"
#include "ui_MenuUI.h"

MenuUI::MenuUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuUI)
{
    ui->setupUi(this);
}

MenuUI::~MenuUI()
{
    delete ui;
}
