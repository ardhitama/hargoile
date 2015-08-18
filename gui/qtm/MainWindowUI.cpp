#include "MainWindowUI.h"
#include "ui_MainWindowUI.h"
#include "../../src/Application/Hargoile.h"
#include <QCloseEvent>

MainWindowUI::MainWindowUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowUI)
{
    ui->setupUi(this);
}

MainWindowUI::~MainWindowUI()
{
    //
}

void MainWindowUI::show()
{
    QMainWindow::show();
}

void MainWindowUI::hide() {}

void MainWindowUI::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->close();
}

void MainWindowUI::close()
{
    //QMainWindow::close();
    Hargoile::getInstance().destroy();
}

void MainWindowUI::setMinimized() {}

void MainWindowUI::setMaximized()
{
    this->setWindowState(windowState() | Qt::WindowMaximized);
    this->showMaximized();
}

void MainWindowUI::toFront()
{
    this->activateWindow();
    this->raise();
}
