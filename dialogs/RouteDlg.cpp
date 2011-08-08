#include "RouteDlg.h"
#include "ui_RouteDlg.h"

RouteDlg::RouteDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteDlg)
{
    ui->setupUi(this);
}

RouteDlg::~RouteDlg()
{
    delete ui;
}
