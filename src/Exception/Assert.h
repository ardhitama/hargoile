#ifndef ASSERT_H
#define ASSERT_H

#ifdef DEBUG

#define TOSTRING(info) TOSTRING2(info)
#define TOSTRING2(info) #info

#define ASSERT(cond) "Assert(\"" TOSTRING(cond) "\", \"" __FILE__ "\", " TOSTRING(__LINE__) ")"
#define FUNCNM "\"" __FUNCSIG__ "\""
#define TRACE "Trace(\"" __FILE__ "\", " TOSTRING(__LINE__) ")"

#else
#define ASSERT(cond) ""
#define FUNCNM ""
#define TRACE ""
#endif // DEBUG

#endif // ASSERT_H
