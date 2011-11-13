#ifndef UIABSTRACT_H
#define UIABSTRACT_H

class UIAbstract
{
public:
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void close() = 0;
    virtual void setMinimized() = 0;
    virtual void setMaximized() = 0;

    virtual void toFront() = 0;

    virtual void setParentUI(UIAbstract *parentUI)
    {
        UIAbstract::parentUI = parentUI;
    }

protected:
    UIAbstract *parentUI;
    UIAbstract()
    {
        parentUI = 0;
    }
};

#endif // UIABSTRACT_H
