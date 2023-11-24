#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"

void initTable(Table *table)
{
    table->count = 0;
    table->capacity = 0;
    table->entries = NULL;
}