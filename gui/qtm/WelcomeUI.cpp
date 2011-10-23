#include "WelcomeUI.h"
#include "../../projects/qt-mobility/ui/ui_WelcomeUI.h"

WelcomeUI::WelcomeUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeUI)
{
    ui->setupUi(this);
}

WelcomeUI::~WelcomeUI()
{
    delete ui;
}
