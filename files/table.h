#ifndef npa_table_h
#define npa_table_h

#include "common.h"
#include "value.h"

typedef struct
{
    int count;
    int capacity;
    Entry *entries;
} Table;

#endif