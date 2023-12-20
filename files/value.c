#include <stdio.h>
#include <string.h>

#include "object.h"
#include "memory.h"
#include "value.h"

// Initializes a dynamic array of values.
void initValueArray(ValueArray *array)
{
    array->values = NULL; // Pointer to the array of values.
    array->capacity = 0;  // How much memory is allocated.
    array->count = 0;     // How many values are currently in the array.
}

// Writes a new value to the end of the dynamic array.
void writeValueArray(ValueArray *array, Value value)
{
    // Increase the array size if needed.
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);                                   // Calculates new capacity.
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity); // Resizes the array.
    }

    // Adds the value to the array and increments the count.
    array->values[array->count] = value;
    array->count++;
}

// Frees the memory used by a value array.
void freeValueArray(ValueArray *array)
{
    FREE_ARRAY(Value, array->values, array->capacity); // Frees the array.
    initValueArray(array);                             // Reinitializes the array structure.
}

// Prints a value for debugging or output purposes.
void printValue(Value value)
{
    switch (value.type)
    {
    case VAL_BOOL:
        printf(AS_BOOL(value) ? "true" : "false"); // Print boolean values.
        break;
    case VAL_NIL:
        printf("nil"); // Print nil (null) values.
        break;
    case VAL_NUMBER:
        printf("%g", AS_NUMBER(value)); // Print numbers.
        break;
    case VAL_OBJ:
        printObject(value); // Delegates to a different function for object values.
        break;
    }
}

// Compares two Value instances for equality.
bool valuesEqual(Value a, Value b)
{
    if (a.type != b.type)
        return false; // Different types means they are not equal.

    switch (a.type)
    {
    case VAL_BOOL:
        return AS_BOOL(a) == AS_BOOL(b); // Compare boolean values.
    case VAL_NIL:
        return true; // Nil values are always equal to each other.
    case VAL_NUMBER:
        return AS_NUMBER(a) == AS_NUMBER(b); // Compare numbers.
    case VAL_OBJ:
        return AS_OBJ(a) == AS_OBJ(b); // Compare object pointers.
    default:
        return false; // Unreachable, all value types should be handled above.
    }
}
