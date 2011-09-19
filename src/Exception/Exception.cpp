#include "Exception.h"

string& Exception::operator <<(string &x)
{
    return x.append(x);
}

