#ifndef npa_memory_h
#define npa_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) \ ((capacity) < 8 ? 8 : (capacity) * 2)

#endif