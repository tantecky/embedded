#ifndef DEBUG_H_OAAUSVHT
#define DEBUG_H_OAAUSVHT

#ifndef NETALARM_TESTING
// (un)comment to enable/disable debugging (Serial.println)
#define NETALARM_DEBUG
#endif

#ifdef NETALARM_DEBUG
#define DEBUG_PRINT(msg) \
  Serial.println(msg)
#else 
#define DEBUG_PRINT(msg) \
  ((void)0)
#endif

#endif /* end of include guard: DEBUG_H_OAAUSVHT */
