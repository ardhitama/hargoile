#include "PopupUI.h"
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QErrorMessage>
#include <QDialog>

PopupUI::PopupUI(const String &strMessage)
{
    /*
    QMessageBox msgBox;
    msgBox.setText(strMessage.data());
    msgBox.exec();
    */

    QMessageBox errDialog;
    //errDialog.showMessage(strMessage.data());
    errDialog.setText(strMessage.data());
    errDialog.exec();
}
