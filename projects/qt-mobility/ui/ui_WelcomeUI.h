/********************************************************************************
** Form generated from reading UI file 'WelcomeUI.ui'
**
** Created: Sun 23. Oct 23:52:06 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEUI_H
#define UI_WELCOMEUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_WelcomeUI
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WelcomeUI)
    {
        if (WelcomeUI->objectName().isEmpty())
            WelcomeUI->setObjectName(QString::fromUtf8("WelcomeUI"));
        WelcomeUI->resize(688, 504);
        buttonBox = new QDialogButtonBox(WelcomeUI);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(9, 240, 156, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(WelcomeUI);
        QObject::connect(buttonBox, SIGNAL(accepted()), WelcomeUI, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WelcomeUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(WelcomeUI);
    } // setupUi

    void retranslateUi(QDialog *WelcomeUI)
    {
        WelcomeUI->setWindowTitle(QApplication::translate("WelcomeUI", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WelcomeUI: public Ui_WelcomeUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEUI_H
