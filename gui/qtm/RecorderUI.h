#ifndef RECORDERUI_H
#define RECORDERUI_H

#include <QDialog>

namespace Ui {
    class RecorderUI;
}

class RecorderUI : public QDialog
{
    Q_OBJECT

public:
    explicit RecorderUI(QWidget *parent = 0);
    ~RecorderUI();

    void show();
    void hide();
    void close();
    void destroy();
    void setMinimized();
    void setMaximized();

private:
    Ui::RecorderUI *ui;
};

#endif // RECORDERUI_H
