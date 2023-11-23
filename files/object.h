#ifndef npa_object_h
#define npa_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_STRING(value) isObjType(value, OBJ_STRING)
typedef enum
{
    OBJ_STRING,
} ObjType;

struct Obj
{
    ObjType type;
};

struct ObjString
{
    Obj obj;
    int length;
    char *chars;
};

#endif