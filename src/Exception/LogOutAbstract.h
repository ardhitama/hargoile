#ifndef LOGOUTABSTRACT_H
#define LOGOUTABSTRACT_H

class LogOutAbstract
{
protected:
    virtual void log(String msg);
    virtual void warning(String msg);
    virtual void error(String msg);
};

#endif // LOGOUTABSTRACT_H
