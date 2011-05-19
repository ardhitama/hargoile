#include "AccountLinkDlg.h"
#include "ui_AccountLinkDlg.h"

AccountLinkDlg::AccountLinkDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountLinkDlg)
{
    ui->setupUi(this);

    linkAct = new QAction("Login", this);
    connect(linkAct,  SIGNAL(triggered()), this, SLOT(doLink()));
    quitAct = new QAction("Quit", this);
    connect(quitAct,  SIGNAL(triggered()), this, SLOT(exitApp()));

    linkAct->setSoftKeyRole(QAction::PositiveSoftKey);
    quitAct->setSoftKeyRole(QAction::NegativeSoftKey);

    this->addAction(linkAct);
    this->addAction(quitAct);
}

void AccountLinkDlg::doLink()
{
    qDebug() << "Linking, Username: " << ui->usernameTxt->text() << " Password: " << ui->passwordTxt->text();
}

void AccountLinkDlg::exitApp()
{
    exit(0);
}

AccountLinkDlg::~AccountLinkDlg()
{
    delete linkAct;
    delete quitAct;
    delete ui;
}
