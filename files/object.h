#ifndef npa_object_h
#define npa_object_h

#include "common.h"
#include "chunk.h"
#include "value.h"

// Macro to get the type of an object.
#define OBJ_TYPE(value) (AS_OBJ(value)->type)

// Macros to check the type of a given value.
#define IS_CLOSURE(value) isObjType(value, OBJ_CLOSURE)
#define IS_FUNCTION(value) isObjType(value, OBJ_FUNCTION)
#define IS_NATIVE(value) isObjType(value, OBJ_NATIVE)
#define IS_STRING(value) isObjType(value, OBJ_STRING)

// Macros to cast a Value to a specific object type.
#define AS_CLOSURE(value) ((ObjClosure *)AS_OBJ(value))
#define AS_FUNCTION(value) ((ObjFunction *)AS_OBJ(value))
#define AS_NATIVE(value) (((ObjNative *)AS_OBJ(value))->function)
#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString *)AS_OBJ(value))->chars)

// Enumeration of different object types in the VM.
typedef enum
{
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE
} ObjType;

// Base structure for all objects.
struct Obj
{
    ObjType type;     // Type of the object.
    bool isMarked;    // Used for garbage collection.
    struct Obj *next; // Next object in the list of all objects.
};

// Structure for a function object.
typedef struct
{
    Obj obj;          // Base object.
    int arity;        // Number of parameters the function takes.
    int upvalueCount; // Number of upvalues the function has.
    Chunk chunk;      // Chunk holding the function's bytecode.
    ObjString *name;  // Function's name.
} ObjFunction;

// Native function pointer type.
typedef Value (*NativeFn)(int argCount, Value *args);

// Structure for a native (C function) object.
typedef struct
{
    Obj obj;           // Base object.
    NativeFn function; // Pointer to the native C function.
} ObjNative;

// Structure for a string object.
struct ObjString
{
    Obj obj;       // Base object.
    int length;    // Length of the string.
    char *chars;   // Pointer to the character data.
    uint32_t hash; // Hash value of the string.
};

// Structure for an upvalue object.
typedef struct ObjUpvalue
{
    Obj obj;                 // Base object.
    Value *location;         // Location of the upvalue.
    Value closed;            // Closed value for the upvalue.
    struct ObjUpvalue *next; // Next upvalue in the chain.
} ObjUpvalue;

// Structure for a closure object.
typedef struct
{
    Obj obj;               // Base object.
    ObjFunction *function; // Pointer to the function object.
    ObjUpvalue **upvalues; // Array of upvalue pointers.
    int upvalueCount;      // Number of upvalues.
} ObjClosure;

// Function declarations for creating new objects.
ObjClosure *newClosure(ObjFunction *function);
ObjFunction *newFunction();
ObjNative *newNative(NativeFn function);
ObjString *takeString(char *chars, int length);
ObjString *copyString(const char *chars, int length);
ObjUpvalue *newUpvalue(Value *slot);
void printObject(Value value);

// Inline function to check if a value is of a specific object type.
static inline bool isObjType(Value value, ObjType type)
{
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
