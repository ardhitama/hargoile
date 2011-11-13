#ifndef RECORDERUI_H
#define RECORDERUI_H

#include <QDialog>
#include <QListView>
#include <QPushButton>

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
    void toStoppedState();
    void toRecordingState();
    void toPausedState();

    void accept();
    void reject();

    void show();
    void hide();
    void close();
    void setMinimized();
    void setMaximized();
    void toFront();

private:
    Ui::RecorderUI *ui;
    QStringListModel positionListModel;

    QPushButton *startBtn, *stopBtn, *menuBtn, *pauseBtn;

private slots:
    void startBtnClicked();
    void stopBtnClicked();
    void pauseBtnClicked();
    void menuBtnClicked();
};

#endif // RECORDERUI_H
