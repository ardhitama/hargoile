#include "PopupUI.h"
#include "QMessageBox"

PopupUI::PopupUI(const String &strMessage)
{
    QMessageBox msgBox;
    msgBox.setText(strMessage.data());
    msgBox.exec();
}
