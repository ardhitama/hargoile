#include "ErrorReporting.h"

ErrorReporting::ErrorReporting()
{
}

ErrorReporting & ErrorReporting::getInstance()
{
    static ErrorReporting report;
    return report;
}
