#include "RecorderUI.h"
#include "ui_RecorderUI.h"
#include "../../src/Application/Hargoile.h"

RecorderUI::RecorderUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecorderUI)
{
    ui->setupUi(this);

    ui->positionListView->setModel(&positionListModel);

    toStoppedState();
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
    ui->positionListView->model()->removeRows(0, ui->positionListView->model()->rowCount());

    startBtn = ui->menuButtonBox->addButton("Start", QDialogButtonBox::YesRole);
    connect(startBtn, SIGNAL(clicked()), SLOT(startBtnClicked()));

    menuBtn = ui->menuButtonBox->addButton("Menu", QDialogButtonBox::NoRole);
    connect(menuBtn, SIGNAL(clicked()), SLOT(menuBtnClicked()));
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
    connect(startBtn, SIGNAL(clicked()), SLOT(startBtnClicked()));

    stopBtn = ui->menuButtonBox->addButton("Stop", QDialogButtonBox::NoRole);
    connect(stopBtn, SIGNAL(clicked()), SLOT(stopBtnClicked()));
}

void RecorderUI::accept(){}
void RecorderUI::reject(){}


void RecorderUI::startBtnClicked()
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
    Hargoile::getInstance().openMenuUI(this);
}

void RecorderUI::show()
{
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
    this->showMaximized();
}

void RecorderUI::toFront()
{
    this->activateWindow();
}
