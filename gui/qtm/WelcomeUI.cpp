#include "WelcomeUI.h"
#include "ui_WelcomeUI.h"

WelcomeUI::WelcomeUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeUI)
{
    ui->setupUi(this);

    ui->passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    if(true)
    {
        ui->menuButtonBox->addButton("Record", QDialogButtonBox::ActionRole);
        ui->menuButtonBox->addButton("Options", QDialogButtonBox::HelpRole);
    }
    else
    {
        ui->menuButtonBox->addButton("Link", QDialogButtonBox::ActionRole);
        ui->menuButtonBox->addButton("Options", QDialogButtonBox::HelpRole);
    }
}

WelcomeUI::~WelcomeUI()
{
    delete ui;
}
