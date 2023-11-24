# bytecode-vm
My own Bytecode Virtual Machine

# DONE:

- SCANNER
- PARSER 
- VM TEMPLATE
- DEBUGGER
- MEMORY CHUNK TEMPLATES
- DATATYPE STRINGS
- HASHTABLES

# TODO:

- GLOBAL/LOCAL VAR
- TRANSITION OF VAR
- FUNCTIONS/CALLS/ETC
- CLOSURES (pina swift)
- GARBAGE COLLECTOR
- OOP (CLASSES INSTANCE INHERITANCE METHODS INITIALIZERS)
- OPTIMIZATION

## Concepts Used

## Bytecode Chunking
#### Dynamic Array of Instructions: 
The bytecode is stored in a dynamic array, which allows constant-time indexed element lookup and appending to the end. This array grows by doubling its capacity to maintain constant amortized time for appends (Hi sir ryan hehe)​​.
#### Growth Strategy: 
The dynamic array starts empty and grows using a function called GROW_CAPACITY, which scales the array's capacity based on its current size. This strategy is designed to utilize memory effectively and maintain performance as elements are added to the array​​.
#### Memory Management: 
Made low-level memory management functions, including allocation, freeing, and resizing memory blocks using a function called reallocate(). This function is a central piece of managing memory for the bytecode's dynamic array​​.

## My Virtual Machine
#### An Instruction Execution Machine: 
In this, the basic structure of a virtual machine (VM) is made, along with its setup and cleanup instructions. A global VM instance is used to keep things simple. The VM type holds the piece of bytecode it's running.

#### Executing Instructions: 
The VM uses the interpret() function to read a chunk of bytecode. This includes running the bytecode instructions and keeping track of an instruction pointer (ip, also knows as the Program Counter [Hi Sir Pers Jang]) that shows where the program is in its execution.

#### Execution Tracing: 
For debugging, the VM can write down each instruction before it is executed. This shows how the disassembleInstruction() function calls automatically interpret and break down bytecode. I also call this the disassembler.

#### A Value Stack Manipulator: 
The VM uses a stack to keep track of the values that instructions make and use. This stack is used to send values from one command to another. It works with a push-and-pop mechanism.

#### The VM's Stack: 
Implemented as a raw C array, the VM's stack handles temporary values and is essential for managing the order of operations and function calls​​.

#### REPL for Stack Tracing: 
A tool for debugging that lets programmers see what's on the stack before each order is carried out. This is especially helpful when working with complicated instructions, and it makes sure that the stack's action is clear. (And in my case, used for testing order precedence from my horribly written parsing method).

## Scanner

#### Interpreter Framework: 
Made the main class and methods for running files and prompts, laying the groundwork for the scanner to operate within​​.

#### Error Handling/Debugger: 
Defined basic error reporting mechanisms, crucial for indicating to users where and what the problems are in their code​​.

#### Lexemes and Tokens: 
This concept involves identifying meaningful character sequences (lexemes) and converting them into tokens with associated metadata like type and value​​. Unwrapping and Wrapping.

#### Regular Languages and Expressions: 
The scanner's logic is based on the principles of regular languages, utilizing patterns similar to regular expressions to identify lexemes​​.

#### The Scanner Class: 
It includes the main loop that iterates over the source code, classifying each character or sequence of characters into tokens, and handling end-of-file (EOF) conditions​​.

#### Recognizing Lexemes: 
Discusses the process of scanning individual tokens, including single-character lexemes and handling of lexical errors​​.

#### Operators: 
Handling of single and multi-character operators, including lookahead to determine if a character is part of a larger lexeme like '!=' versus '!'​​. [Also discovered how switch case statements are faster than if else statements]

#### Longer Lexemes: 
Strategies for lexemes that span multiple characters, such as comments or strings, which may require specialized scanning logic​​. (Simply another switch case)

## Compiler

#### Single-Pass Compilation: 
The compilation process that merges parsing and code generation into one pass.

#### THE PRATT PARSER: 
wikipedia nalang ta ani (basta chose this kay its more power than LR Descent Parsing and RELATIVELY simple to implement)
The Pratt parser, introduced by Vaughan Pratt, is an elegant parsing technique that efficiently handles various expression grammars, including infix, prefix, and postfix operators, with different levels of precedence and associativity. It's particularly known for its simplicity and power, making it a favorite among language implementers for handwritten parsers.

Pratt parsers work by associating parsing functions with token types. Each token type can have up to two parsing functions: one for when the token appears as a prefix (like - in -a) and another for when it appears as an infix (like + in a + b). These functions are then used in a parsing table to direct the parsing process as tokens are read from the input.

The parser maintains a notion of "current token" and executes the corresponding parsing function based on the token's role (prefix or infix). This function can then decide how to parse the following tokens, potentially invoking other parsing functions recursively, allowing for a natural and efficient handling of operator precedence and associativity.

The Pratt parser shines with its ability to parse a wide variety of expression patterns using a relatively small and consistent set of parsing rules, and it's well-suited for programming languages with complex expression syntax. It's an algorithm often used in production compilers for its balance of performance and maintainability.

#### Emitting Bytecode: 
After parsing, the compiler translates the source code into bytecode instructions​​.

#### Parsing Prefix Expressions: 
How the compiler handles expressions that start with a specific token, like unary operators or parentheses​​.

#### Unary Negation: 
It specifically addresses how the compiler deals with the unary minus operator, including the order of bytecode emission relative to operand parsing​​.

## Value Types

#### Tagged Unions: 
This concept involves using a combination of enums and unions in C to represent different types of values that a variable can hold in a dynamically typed language. The enum indicates the type of the value, and the union holds the actual data​​.

#### NVM Values and C Values: 
Conversion between native C values and the interpreter's value types is handled through macros. These macros are responsible for wrapping C values into the interpreter's value types and for unwrapping the interpreter's values back into C values​​.

#### Dynamically Typed Numbers: 
This part addresses the necessary changes in the code to handle the new representation of values. It also describes the implementation of runtime checks and errors for operations that are type-dependent, like unary negation​​.

#### Two New Types: 
Introduction of Boolean and nil literals in the interpreter, and the implementation of specialized instructions for these literals to optimize performance and memory usage​​.

## STRINGS (PINAKACONFUSING NA PART ANI TANAN)

#### String Representation: 
The interpreter is designed to handle string values by tokenizing string literals and creating string objects to represent them in the language. This is done by trimming the leading and trailing quotation marks from the lexeme and then creating an ObjString object​​ (HEAP MOMENTS).

#### String Operations: 
Made support for string operations (concatenations). For example, it includes a specialized instruction for each of the literals true, false, and nil, and it defines operations for printing string objects and comparing string equality based on the characters they contain​​.

#### String Concatenation: 
In NVM, strings can be concatenated using the + operator. This involves creating a new string that merges the characters of the two operand strings. This is a runtime operation, as the types of the operands are not known until runtime due to NVM's dynamic typing​​.

#### Memory Management: 
Strings are dynamically allocated, which introduces the potential for memory leaks. Started to make garbage collection techniques (but is not complete) to manage memory and prevent leaks. Until PROPER garbage collection is implemented, I made a simpler approach by maintaining a linked list of all objects to ensure they can be found and freed when no longer in use​​. (in this case if string loc is > program counter or ip)

## Hash Tables for Variable Tracking (OKAY NEVERMIND NAGKALISUD NA)

#### An Array of Buckets: 
Simplified the basic structure of a hash table and set it as an array where each element, called a bucket, can potentially hold a key-value pair​​.

#### Collision Resolution:  
Found ways for hash tables deal with collisions—situations where different keys hash to the same bucket. Techniques include separate chaining and open addressing​​. I DID OPEN ADDRESSING (aka closed hasing)

#### Hash Functions: 
Used the Fowler–Noll–Vo hash function as the hash function (why? kay usa ra ka formula therefore sayun i implement)

#### Building a Hash Table: 
Made implementation details of creating a hash table in the context of the language, including managing the array of buckets and handling dynamic resizing to maintain a balanced load factor​​.

#### Inserting and Setting Entries: 
Made functions for the process of adding entries to the hash table, handling new keys, and overwriting existing ones, as well as ensuring the hash table has enough capacity for new entries​​​​


