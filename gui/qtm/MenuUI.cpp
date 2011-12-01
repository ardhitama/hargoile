#include "MenuUI.h"
#include "ui_MenuUI.h"
#include "../../src/Application/Hargoile.h"

MenuUI::MenuUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuUI)
{
    ui->setupUi(this);

    ui->reducedRouteUploadBtn->hide();
    ui->routeUploadBtn->hide();
    ui->newRouteBtn->hide();
    ui->testRouteUploadBtn->hide();
    ui->unlinkBtn->hide();

    backBtn = ui->menuButtonBox->addButton("Back", QDialogButtonBox::NoRole);
    connect(backBtn, SIGNAL(clicked()), SLOT(backBtnClicked()));

}

MenuUI::~MenuUI()
{
    delete ui;
}

void MenuUI::setMenuType(int menuType)
{
    ui->reducedRouteUploadBtn->hide();
    ui->routeUploadBtn->hide();
    ui->newRouteBtn->hide();
    ui->testRouteUploadBtn->hide();
    ui->unlinkBtn->hide();

    switch(menuType)
    {
    case WELCOME_MENU:
        ui->unlinkBtn->show();
        break;
    case RECORDER_MENU:
        ui->reducedRouteUploadBtn->show();
        ui->routeUploadBtn->show();
        ui->newRouteBtn->show();
        ui->testRouteUploadBtn->show();
        break;
    }
}

void MenuUI::backBtnClicked()
{
    this->close();
}

void MenuUI::on_routeUploadBtn_clicked()
{
    Hargoile::getInstance().uploadRoute(Hargoile::getInstance().getCurrentRoute());
    //if(parentUI != 0)
        //parentUI->close();
    //Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    //close();
}

void MenuUI::on_reducedRouteUploadBtn_clicked()
{
    Route route = Hargoile::getInstance().getReducedCurrentRoute();
    Hargoile::getInstance().uploadRoute(route);
    //if(parentUI != 0)
        //parentUI->close();
    //Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    //close();
}

void MenuUI::on_quitBtn_clicked()
{
    Hargoile::getInstance().destroy();
}
void MenuUI::on_unlinkBtn_clicked()
{
    Hargoile::getInstance().unlinkAccount();
    if(parentUI != 0)
        parentUI->close();
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_WELCOME);
    close();
}

void MenuUI::on_newRouteBtn_clicked()
{
    if(parentUI != 0)
        parentUI->close();
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    close();
}

void MenuUI::on_testRouteUploadBtn_clicked()
{
    Route route = Hargoile::getInstance().getCurrentRoute();
    Route route1 = Hargoile::getInstance().getCurrentRoute();
    Route route2 = Hargoile::getInstance().getCurrentRoute();
    Route route3 = Hargoile::getInstance().getCurrentRoute();

    route.generateUUID();
    route1.generateUUID();
    route2.generateUUID();
    route3.generateUUID();

    route.setName(route.getName() << " [" << Hargoile::getInstance().getCurrentAccuracyTolerance() << "][0.0]");
    route1.setName(route1.getName() << " [" << Hargoile::getInstance().getCurrentAccuracyTolerance() << "][1.0]");
    route2.setName(route2.getName() << " [" << Hargoile::getInstance().getCurrentAccuracyTolerance() << "][2.0]");
    route3.setName(route3.getName() << " [" << Hargoile::getInstance().getCurrentAccuracyTolerance() << "][3.0]");

    route1.simplify(1.0f);
    route2.simplify(2.0f);
    route3.simplify(3.0f);

    Hargoile::getInstance().uploadRoute(route);
    Hargoile::getInstance().uploadRoute(route1);
    Hargoile::getInstance().uploadRoute(route2);
    Hargoile::getInstance().uploadRoute(route3);

    //if(parentUI != 0)
        //parentUI->close();
    //Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    //close();
}

void MenuUI::show()
{
    //this->exec();
    this->open();
}

void MenuUI::hide() {}

void MenuUI::close()
{
    if(parentUI != 0)
        parentUI->toFront();
    this->done(0);
}

void MenuUI::setMinimized() {}

void MenuUI::setMaximized()
{
    this->showMaximized();
}

void MenuUI::toFront()
{
    this->activateWindow();
}
