#ifndef UIABSTRACT_H
#define UIABSTRACT_H

class UIAbstract
{
public:
	virtual void show() {};
	virtual void hide() {};
	virtual void close() {};
	virtual void setMinimized() {};
	virtual void setMaximized() {};

	virtual void toFront() {};

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
