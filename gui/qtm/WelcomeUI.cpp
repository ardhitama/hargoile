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

    ui->infoLabel->setText("Your Account Is Already Linked");

    ui->infoLabel->setVisible(true);
    ui->loginFrame->setVisible(false);

    startBtn = ui->menuButtonBox->addButton("Record", QDialogButtonBox::YesRole);
    connect(startBtn, SIGNAL(clicked()), SLOT(recordBtnClicked()));

    menuBtn = ui->menuButtonBox->addButton("Menu", QDialogButtonBox::NoRole);
    connect(menuBtn, SIGNAL(clicked()), SLOT(menuBtnClicked()));
}

void WelcomeUI::toNotLinkedState()
{
    ui->menuButtonBox->clear();
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();

    ui->infoLabel->setText("Please Link Your Account");

    ui->infoLabel->setVisible(false);
    ui->loginFrame->setVisible(true);

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

void WelcomeUI::menuBtnClicked()
{
    Hargoile::getInstance().openMenuUI(this, MenuUI::WELCOME_MENU);
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
    this->setWindowState(windowState() | Qt::WindowMaximized);
    this->showMaximized();
}

void WelcomeUI::toFront()
{
    this->activateWindow();
    this->raise();
}
