# bytecode-vm
My own Bytecode Virtual Machine

## Concepts Used

### Bytecode Chunking
#### Dynamic Array of Instructions: 
The bytecode is stored in a dynamic array, which allows constant-time indexed element lookup and appending to the end. This array grows by doubling its capacity to maintain constant amortized time for appends (Hi sir ryan hehe)​​.
#### Growth Strategy: 
The dynamic array starts empty and grows using a function called GROW_CAPACITY, which scales the array's capacity based on its current size. This strategy is designed to utilize memory effectively and maintain performance as elements are added to the array​​.
#### Memory Management: 
Made low-level memory management functions, including allocation, freeing, and resizing memory blocks using a function called reallocate(). This function is a central piece of managing memory for the bytecode's dynamic array​​.

### My Virtual Machine
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


