#ifndef UIABSTRACT_H
#define UIABSTRACT_H

class UIAbstract
{
protected:
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void close() = 0;
    virtual void destroy() = 0;
    virtual void setMinimized() = 0;
    virtual void setMaximized() = 0;
};

#endif // UIABSTRACT_H
