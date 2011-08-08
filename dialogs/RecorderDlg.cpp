#include "RecorderDlg.h"
#include "ui_RecorderDlg.h"

RecorderDlg::RecorderDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecorderDlg)
{
    ui->setupUi(this);
}

RecorderDlg::~RecorderDlg()
{
    delete ui;
}
