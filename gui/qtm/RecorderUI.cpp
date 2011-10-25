#include "RecorderUI.h"
#include "ui_RecorderUI.h"

RecorderUI::RecorderUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecorderUI)
{
    ui->setupUi(this);
    ui->menuButtonBox->addButton("Start", QDialogButtonBox::YesRole);
    ui->menuButtonBox->addButton("Stop", QDialogButtonBox::NoRole);
}

RecorderUI::~RecorderUI()
{
    delete ui;
}
