// This is an include guard. It prevents the file from being included more than once.
#ifndef npa_common_h
#define npa_common_h

// These are standard library includes. They provide various types and functions.
#include <stdbool.h> // Provides a boolean type and the values true and false.
#include <stddef.h>  // Provides various types and macros.
#include <stdint.h>  // Provides exact-width integer types.

// These are debug flags. They control whether certain debug information is printed.
#define DEBUG_PRINT_CODE      // If defined, the code will be printed for debugging.
#define DEBUG_TRACE_EXECUTION // If defined, the execution of the code will be traced for debugging.

// These are commented out debug flags. They could be used to enable additional debugging features.
// #define DEBUG_BYTECODE     // If defined, the bytecode will be printed for debugging.
// #define DEBUG_STRESS_GC   // If defined, the garbage collector will be stressed for debugging.
// #define DEBUG_LOG_GC      // If defined, the garbage collector will be logged for debugging.

// This is a constant that represents the number of possible values of a uint8_t.
#define UINT8_COUNT (UINT8_MAX + 1)

// This is the end of the include guard.
#endif