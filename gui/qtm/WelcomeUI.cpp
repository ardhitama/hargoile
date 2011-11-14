#include "WelcomeUI.h"
#include "ui_WelcomeUI.h"
#include "../../src/Application/Hargoile.h"

WelcomeUI::WelcomeUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeUI)
{
    ui->setupUi(this);

    ui->passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    if(Hargoile::getInstance().isAccountLinked())
        toLinkedState();
    else
        toNotLinkedState();

}

void WelcomeUI::toLinkedState()
{
    ui->menuButtonBox->clear();

    ui->loginFrame->setEnabled(false);

    startBtn = ui->menuButtonBox->addButton("Record", QDialogButtonBox::YesRole);
    connect(startBtn, SIGNAL(clicked()), SLOT(recordBtnClicked()));

    quitBtn = ui->menuButtonBox->addButton("Quit", QDialogButtonBox::NoRole);
    connect(quitBtn, SIGNAL(clicked()), SLOT(quitBtnClicked()));
}

void WelcomeUI::toNotLinkedState()
{
    ui->menuButtonBox->clear();

    ui->loginFrame->setEnabled(true);

    linkBtn = ui->menuButtonBox->addButton("Link", QDialogButtonBox::YesRole);
    connect(linkBtn, SIGNAL(clicked()), SLOT(linkBtnClicked()));

    quitBtn = ui->menuButtonBox->addButton("Quit", QDialogButtonBox::NoRole);
    connect(quitBtn, SIGNAL(clicked()), SLOT(quitBtnClicked()));
}

void WelcomeUI::recordBtnClicked()
{
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    close();
}

void WelcomeUI::linkBtnClicked()
{
    Hargoile::getInstance().linkAccount(ui->usernameLineEdit->text().toStdString(), ui->passwordLineEdit->text().toStdString());
}

void WelcomeUI::quitBtnClicked()
{
    Hargoile::getInstance().destroy();
}

WelcomeUI::~WelcomeUI()
{
    delete ui;
}

void WelcomeUI::show()
{
    this->exec();
}

void WelcomeUI::hide() {}
void WelcomeUI::close()
{
    this->done(0);
}

void WelcomeUI::setMinimized() {}

void WelcomeUI::setMaximized()
{
    this->showMaximized();
}

void WelcomeUI::toFront()
{
    this->activateWindow();
}
