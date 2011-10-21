#ifndef ERRORNOTIFICATIONIMPL_H
#define ERRORNOTIFICATIONIMPL_H

#include "../ErrorNotification.h"
#include "../../Utility/String.h"
#include <iostream>

class ErrorNotificationImpl : public ErrorNotification
{
public:
	static void textOut(String msg)
	{
		std::cout << msg << std::endl;
	}
};

#endif // ERRORNOTIFICATIONIMPL_H
