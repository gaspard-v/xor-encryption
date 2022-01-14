#ifndef DEBUG_H
#define DEBUG_H
#ifdef ENABLE_DEBUG
#define DEBUG_PRINT(x) fprintf x;	
#else
#define DEBUG_PRINT(x)
#endif
#endif