#ifndef ROUTEDLG_H
#define ROUTEDLG_H

#include <QDialog>

namespace Ui {
    class RouteDlg;
}

class RouteDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RouteDlg(QWidget *parent = 0);
    ~RouteDlg();

private:
    Ui::RouteDlg *ui;
};

#endif // ROUTEDLG_H
