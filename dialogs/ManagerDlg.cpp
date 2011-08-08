#include "ManagerDlg.h"
#include "ui_ManagerDlg.h"

ManagerDlg::ManagerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagerDlg)
{
    ui->setupUi(this);
}

ManagerDlg::~ManagerDlg()
{
    delete ui;
}
