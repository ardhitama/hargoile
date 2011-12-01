#include <QApplication>
#include <QDialog>
#include "Application/Hargoile.h"

class App : public QApplication
{
public:
    App(int argc, char** argv) : QApplication(argc, argv)
    {
        backDlg = new QDialog();
        backDlg->show();
    }

    ~App()
    {
        backDlg->close();
    }

    bool notify(QObject * receiver, QEvent * event)
    {
        try
        {
            return QApplication::notify(receiver, event);
        }
        catch(Exception &e)
        {
            LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
        }
        return false;
    }
private:
    QDialog *backDlg;
};

int main(int argc, char *argv[])
{
    App app(argc, argv);
    Hargoile::getInstance().init();
    Hargoile::getInstance().run();
    return app.exec();
}
