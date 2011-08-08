#ifndef RECORDERDLG_H
#define RECORDERDLG_H

#include <QDialog>

namespace Ui {
    class RecorderDlg;
}

class RecorderDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RecorderDlg(QWidget *parent = 0);
    ~RecorderDlg();

private:
    Ui::RecorderDlg *ui;
};

#endif // RECORDERDLG_H
