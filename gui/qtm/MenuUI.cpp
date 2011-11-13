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
}

void MenuUI::on_reducedRouteUploadBtn_clicked()
{
    Route route = Hargoile::getInstance().getReducedCurrentRoute();
    Hargoile::getInstance().uploadRoute(route);
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
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_WELCOME);
    close();
}

void MenuUI::show()
{
    this->exec();
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
