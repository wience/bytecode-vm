#ifndef npa_compiler_h
#define npa_compiler_h

#include "vm.h"
#include "object.h"

// #include "chunk.h"

ObjFunction *compile(const char *source);

#endif