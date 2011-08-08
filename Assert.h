#ifndef ASSERT_H
#define ASSERT_H

#ifdef DEBUG
#include "iostream"

#undef ASSERT
#undef TRACE

#define ASSERT(cond) {if(!cond){ std::cerr<< #cond << __FILE__ << __LINE__ << endl; }}
#define TRACE(info) {std::cerr<< info << __FILE__ << __LINE__ << endl;}

#else
#define ASSERT(cond) ({})
#define TRACE(info) ({})
#endif // DEBUG

#endif // ASSERT_H
