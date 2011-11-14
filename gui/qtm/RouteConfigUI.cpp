#include "RouteConfigUI.h"
#include "ui_RouteConfigUI.h"
#include "../../src/Application/Hargoile.h"

RouteConfigUI::RouteConfigUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteConfigUI)
{
    ui->setupUi(this);

    ui->toleranceDoubleSpinBox->setMinimum(0.0f);
    ui->toleranceDoubleSpinBox->setMaximum(5000.0f);
    ui->toleranceDoubleSpinBox->setSingleStep(0.1f);
    ui->toleranceDoubleSpinBox->setValue(Hargoile::getInstance().getCurrentDPTolerance());

    ui->accuracySpinBox->setMinimum(0);
    ui->accuracySpinBox->setMaximum(90);
    ui->accuracySpinBox->setSingleStep(1);
    ui->accuracySpinBox->setValue(Hargoile::getInstance().getCurrentAccuracyTolerance());

    continueBtn = ui->menuButtonBox->addButton("Continue", QDialogButtonBox::YesRole);
    connect(continueBtn, SIGNAL(clicked()), SLOT(continueBtnClicked()));

    backBtn = ui->menuButtonBox->addButton("Back", QDialogButtonBox::NoRole);
    connect(backBtn, SIGNAL(clicked()), SLOT(backBtnClicked()));
}

void RouteConfigUI::continueBtnClicked()
{
    Hargoile::getInstance().getCurrentRoute().setName(ui->nameLineEdit->text().toStdString());
    Hargoile::getInstance().setCurrentDPTolerance(ui->toleranceDoubleSpinBox->value());
    Hargoile::getInstance().setCurrentAccuracyTolerance(ui->accuracySpinBox->value());
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_RECORDER);
    close();
}

void RouteConfigUI::backBtnClicked()
{
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_WELCOME);
    close();
}

void RouteConfigUI::show()
{
    this->exec();
}

void RouteConfigUI::hide() {}

void RouteConfigUI::close()
{
    this->done(0);
}

void RouteConfigUI::setMinimized() {}

void RouteConfigUI::setMaximized()
{
    this->showMaximized();
}

RouteConfigUI::~RouteConfigUI()
{
    delete ui;
}

void RouteConfigUI::toFront()
{
    this->activateWindow();
}
