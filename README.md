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

