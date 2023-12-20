// Standard libraries for input/output, memory management, and string operations.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Project-specific headers for common definitions, chunk data structures, debugging, and the virtual machine.
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

// REPL (Read-Eval-Print Loop) function for interactive execution.
static void repl()
{
    char line[1024]; // Buffer for input line.
    for (;;)
    {
        printf("> "); // Prompt symbol.

        // Reads a line of input. If input fails (e.g., EOF), exit the loop.
        if (!fgets(line, sizeof(line), stdin))
        {
            printf("\n");
            break;
        }

        // Interprets the input line.
        interpret(line);
    }
}

// Function to read the contents of a file into a string.
static char *readFile(const char *path)
{
    // Opens the file in binary mode.
    FILE *file = fopen(path, "rb");

    // Error handling if the file couldn't be opened.
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74); // Exit with a file-related error code.
    }

    // Gets the size of the file.
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    // Allocates memory for the file contents plus a null terminator.
    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL)
    {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74); // Exit with a memory-related error code.
    }

    // Reads the file into the buffer.
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize)
    {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74); // Exit on read error.
    }

    buffer[bytesRead] = '\0'; // Null-terminates the string.

    fclose(file);  // Closes the file.
    return buffer; // Returns the file contents as a string.
}

// Function to run a script from a file.
static void runFile(const char *path)
{
    char *source = readFile(path);              // Reads the file contents.
    InterpretResult result = interpret(source); // Interprets the script.
    free(source);                               // Frees the memory allocated for the script.

    // Exits with specific error codes based on the result of interpretation.
    if (result == INTERPRET_COMPILE_ERROR)
        exit(65);
    if (result == INTERPRET_RUNTIME_ERROR)
        exit(70);
}

// Main function: Entry point of the program.
int main(int argc, const char *argv[])
{
    initVM(); // Initializes the virtual machine.

    // Determines the mode of operation based on command-line arguments.
    if (argc == 1)
    {
        repl(); // Starts the REPL for interactive execution.
    }
    else if (argc == 2)
    {
        runFile(argv[1]); // Executes a script file.
    }
    else
    {
        fprintf(stderr, "Usage: npa [path]\n"); // Error message for incorrect usage.
        exit(64);                               // Exits with a usage error code.
    }

    freeVM(); // Cleans up and frees the virtual machine.
    return 0; // Successful exit.
}
