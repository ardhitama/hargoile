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

void AccountLinkDlg::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void AccountLinkDlg::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    showMaximized();
#else
    show();
#endif
}

AccountLinkDlg::~AccountLinkDlg()
{
    delete linkAct;
    delete quitAct;
    delete ui;
}
