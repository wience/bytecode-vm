#ifndef npa_compiler_h
#define npa_compiler_h

#include "vm.h"
#include "object.h"

// #include "chunk.h"

bool compile(const char *source, Chunk *chunk);

#endif