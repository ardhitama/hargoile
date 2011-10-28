#ifndef RECORDERUI_H
#define RECORDERUI_H

#include <QDialog>
#include <QListView>

#include <QStringList>
#include <QStringListModel>

#include "../../src/Utility/String.h"
#include "../UIAbstract.h"

namespace Ui {
    class RecorderUI;
}

class RecorderUI : public QDialog, virtual public UIAbstract
{
    Q_OBJECT

public:
    explicit RecorderUI(QWidget *parent = 0);
    ~RecorderUI();

    void appendPositionListView(const String &str);

    void accept();
    void reject();

    void show();
    void hide();
    void close();
    void destroy();
    void setMinimized();
    void setMaximized();

private:
    Ui::RecorderUI *ui;
    QStringListModel positionListModel;

private slots:
    void startBtnClicked();
};

#endif // RECORDERUI_H
