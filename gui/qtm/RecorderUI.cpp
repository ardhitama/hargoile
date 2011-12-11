#include "RecorderUI.h"
#include "ui_RecorderUI.h"
#include "../../src/Application/Hargoile.h"

RecorderUI::RecorderUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecorderUI)
{
    ui->setupUi(this);
}

RecorderUI::~RecorderUI()
{
    delete ui;
}

void RecorderUI::appendPositionListView(const String &str)
{
    ui->positionListView->model()->insertRow(ui->positionListView->model()->rowCount());
    ui->positionListView->model()->setData(ui->positionListView->model()->index(ui->positionListView->model()->rowCount()-1, 0), str.data());
    ui->positionListView->scrollTo(ui->positionListView->model()->index(ui->positionListView->model()->rowCount()-1, 0));
}

void RecorderUI::toStoppedState()
{
    ui->menuButtonBox->clear();

    menuBtn = ui->menuButtonBox->addButton("Menu", QDialogButtonBox::NoRole);
    connect(menuBtn, SIGNAL(clicked()), SLOT(menuBtnClicked()));
}

void RecorderUI::toInitState()
{
    ui->menuButtonBox->clear();

    positionListModel.removeRows(0, positionListModel.rowCount());
    ui->positionListView->setModel(&positionListModel);

    startBtn = ui->menuButtonBox->addButton("Start", QDialogButtonBox::YesRole);
    connect(startBtn, SIGNAL(clicked()), SLOT(startBtnClicked()));

    backBtn = ui->menuButtonBox->addButton("Back", QDialogButtonBox::NoRole);
    connect(backBtn, SIGNAL(clicked()), SLOT(backBtnClicked()));
}

void RecorderUI::toRecordingState()
{
    ui->menuButtonBox->clear();

    pauseBtn = ui->menuButtonBox->addButton("Pause", QDialogButtonBox::YesRole);
    connect(pauseBtn, SIGNAL(clicked()), SLOT(pauseBtnClicked()));

    stopBtn = ui->menuButtonBox->addButton("Stop", QDialogButtonBox::NoRole);
    connect(stopBtn, SIGNAL(clicked()), SLOT(stopBtnClicked()));
}

void RecorderUI::toPausedState()
{
    ui->menuButtonBox->clear();

    startBtn = ui->menuButtonBox->addButton("Resume", QDialogButtonBox::YesRole);
    connect(startBtn, SIGNAL(clicked()), SLOT(resumeBtnClicked()));

    stopBtn = ui->menuButtonBox->addButton("Stop", QDialogButtonBox::NoRole);
    connect(stopBtn, SIGNAL(clicked()), SLOT(stopBtnClicked()));
}

void RecorderUI::accept(){}
void RecorderUI::reject(){}


void RecorderUI::startBtnClicked()
{
    ui->positionListView->model()->removeRows(0, ui->positionListView->model()->rowCount());
    Hargoile::getInstance().startRouteRecording();
}

void RecorderUI::resumeBtnClicked()
{
    Hargoile::getInstance().startRouteRecording();
}

void RecorderUI::stopBtnClicked()
{
    Hargoile::getInstance().stopRouteRecording();
}

void RecorderUI::pauseBtnClicked()
{
    Hargoile::getInstance().pauseRouteRecording();
}

void RecorderUI::menuBtnClicked()
{
    Hargoile::getInstance().openMenuUI(this, MenuUI::RECORDER_MENU);
}

void RecorderUI::backBtnClicked()
{
    Hargoile::getInstance().getUIQueue().push(Hargoile::UI_ROUTECONFIG);
    close();
}

void RecorderUI::show()
{
    toInitState();
    this->exec();
}

void RecorderUI::hide() {}

void RecorderUI::close()
{
    this->done(0);
}

void RecorderUI::setMinimized() {}

void RecorderUI::setMaximized()
{
    this->setWindowState(windowState() | Qt::WindowMaximized);
    this->showMaximized();
}

void RecorderUI::toFront()
{
    this->activateWindow();
    this->raise();
}
