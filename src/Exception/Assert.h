#ifndef ASSERT_H
#define ASSERT_H

#ifdef DEBUG

#undef ASSERT
#undef TRACE

#define ASSERT(cond) (cond) ? "Assertion: " ## cond ## " in " ## __FILE__ ## " (" ##  __LINE__ ## ")" : ""
#define TRACE "Trace: "__FILE__ ## " (" ## #__LINE__ ## ")"

#else
#define ASSERT(cond) ""
#define TRACE ""
#endif // DEBUG

#endif // ASSERT_H
