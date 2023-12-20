// Including standard I/O library and project-specific headers.
#include <stdio.h>
#include "debug.h"
#include "object.h"
#include "value.h"

// Disassembles a chunk of bytecode, printing its operations in a readable format.
void disassembleChunk(Chunk *chunk, const char *name)
{
    printf("== %s ==\n", name); // Header for the disassembly section.

    // Iterates through each byte in the chunk, disassembling instructions.
    for (int offset = 0; offset < chunk->count;)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}

// Handles the disassembly of instructions that involve constants.
static int constantInstruction(const char *name, Chunk *chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1];    // Gets the constant index from the bytecode.
    printf("%-16s %4d '", name, constant);         // Prints the operation name and constant index.
    printValue(chunk->constants.values[constant]); // Prints the constant value.
    printf("'\n");
    return offset + 2; // Moves past the operation and constant index in the bytecode.
}

// Handles the disassembly of simple instructions (no operands).
static int simpleInstruction(const char *name, int offset)
{
    printf("%s\n", name); // Prints the operation name.
    return offset + 1;    // Moves to the next instruction in the bytecode.
}

// Handles the disassembly of instructions that involve a single byte as an operand.
static int byteInstruction(const char *name, Chunk *chunk, int offset)
{
    uint8_t slot = chunk->code[offset + 1]; // Gets the operand from the bytecode.
    printf("%16s %4d\n", name, slot);       // Prints the operation name and operand.
    return offset + 2;                      // Moves past the operation and operand in the bytecode.
}

// Handles the disassembly of jump instructions, which involve jump offsets.
static int jumpInstruction(const char *name, int sign, Chunk *chunk, int offset)
{
    // Calculates the jump offset from two bytes in the bytecode.
    uint16_t jump = (uint16_t)(chunk->code[offset + 1] << 8);
    jump |= chunk->code[offset + 2];
    printf("%-16s %4d -> %d\n", name, offset, offset + 3 + sign * jump); // Prints the operation, current offset, and jump destination.
    return offset + 3;                                                   // Moves past the operation and jump offset in the bytecode.
}

// Main function to disassemble an instruction at a given offset in a chunk.
int disassembleInstruction(Chunk *chunk, int offset)
{
    printf("%04d ", offset); // Prints the offset of the instruction in the bytecode.

    // Prints line numbers or a marker to indicate same line as previous instruction.
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
    {
        printf("   | ");
    }
    else
    {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instruction = chunk->code[offset]; // Gets the instruction from the bytecode.
    switch (instruction)                       // Dispatches based on the instruction type.
    {
    // Handles different instruction types, calling appropriate functions.
    // ...
    case OP_CLOSURE:
    {
        // Special handling for OP_CLOSURE, which includes function and upvalues details.
        // ...
    }
    // ... (handling other instructions)
    default:
        printf("Unknown opcode %d\n", instruction); // Handles unknown opcodes.
        return offset + 1;
    }
}

// Prints the raw bytecode in a chunk, along with line numbers.
void printBytecode(Chunk *chunk)
{
    printf("Bytecode (Count: %d):\n", chunk->count); // Header for the bytecode section.
    for (int i = 0; i < chunk->count; i++)           // Iterates through each byte in the chunk.
    {
        printf("%02x ", chunk->code[i]); // Prints the bytecode in hex format.
        // Prints line numbers at specific intervals or at the end of the chunk.
        if ((i + 1) % 8 == 0 || i == chunk->count - 1)
        {
            printf("\t(line %d)\n", chunk->lines[i]);
        }
    }
    printf("\n");
}
