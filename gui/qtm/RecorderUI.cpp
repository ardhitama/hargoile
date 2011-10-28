#include "RecorderUI.h"
#include "ui_RecorderUI.h"
#include <QPushButton>
#include "../../src/Application/Hargoile.h"

RecorderUI::RecorderUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecorderUI)
{
    ui->setupUi(this);

    ui->positionListView->setModel(&positionListModel);

    QPushButton *menuBtn;
    menuBtn = ui->menuButtonBox->addButton("Start", QDialogButtonBox::YesRole);
    connect(menuBtn, SIGNAL(clicked()), SLOT(startBtnClicked()));

    ui->menuButtonBox->addButton("Stop", QDialogButtonBox::NoRole);
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

void RecorderUI::accept(){}
void RecorderUI::reject(){}


void RecorderUI::startBtnClicked()
{
    Hargoile::getInstance().startRouteRecording();
}

void RecorderUI::show()
{
    this->exec();
}

void RecorderUI::hide() {}
void RecorderUI::close() {}
void RecorderUI::destroy() {}
void RecorderUI::setMinimized() {}

void RecorderUI::setMaximized()
{
    this->showMaximized();
}
