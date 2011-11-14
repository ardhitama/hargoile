#include "MenuUI.h"
#include "ui_MenuUI.h"
#include "../../src/Application/Hargoile.h"

MenuUI::MenuUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuUI)
{
    ui->setupUi(this);

    backBtn = ui->menuButtonBox->addButton("Back", QDialogButtonBox::NoRole);
    connect(backBtn, SIGNAL(clicked()), SLOT(backBtnClicked()));

}

MenuUI::~MenuUI()
{
    delete ui;
}

void MenuUI::backBtnClicked()
{
    this->close();
}

void MenuUI::on_routeUploadBtn_clicked()
{
    Hargoile::getInstance().uploadRoute(Hargoile::getInstance().getCurrentRoute());
    if(parentUI != 0)
        parentUI->close();
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    close();
}

void MenuUI::on_reducedRouteUploadBtn_clicked()
{
    Route route = Hargoile::getInstance().getReducedCurrentRoute();
    Hargoile::getInstance().uploadRoute(route);
    if(parentUI != 0)
        parentUI->close();
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    close();
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

    route.setName(route.getName() << " [raw][test]");
    route1.setName(route1.getName() << " [1.0][test]");
    route2.setName(route2.getName() << " [2.0][test]");
    route3.setName(route3.getName() << " [3.0][test]");

    route1.simplify(1.0f);
    route2.simplify(2.0f);
    route3.simplify(3.0f);

    Hargoile::getInstance().uploadRoute(route);
    Hargoile::getInstance().uploadRoute(route1);
    Hargoile::getInstance().uploadRoute(route2);
    Hargoile::getInstance().uploadRoute(route3);

    if(parentUI != 0)
        parentUI->close();
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    close();
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
