# Memory Maps

## Program: stack_example.c

### Program Overview

This program demonstrates how stack frames are created and destroyed during recursive function calls. It does not perform any dynamic memory allocation, so the heap remains unused throughout execution.

---

## Execution Point 1 – Program Start

`main()` begins execution and calls `walk_stack(0, 3)`.

### Stack

```
+----------------------+
| main()               |
+----------------------+
```

### Heap

```
(empty)
```

### Explanation

- Only the `main()` stack frame exists.
- No heap memory has been allocated.

---

## Execution Point 2 – Entering `walk_stack(0, 3)`

A new stack frame is created.

### Stack

```
+-------------------------+
| walk_stack(depth = 0)   |
| marker = 0              |
+-------------------------+
| main()                  |
+-------------------------+
```

### Heap

```
(empty)
```

### Explanation

- `marker` is a local variable stored on the stack.
- Its lifetime begins when `walk_stack()` starts and ends when the function returns.

---

## Execution Point 3 – Entering `dump_frame()`

Another stack frame is pushed onto the stack.

### Stack

```
+----------------------------+
| dump_frame()               |
| local_int = 100            |
| local_buf[16]              |
| p_local --> local_int      |
+----------------------------+
| walk_stack(depth = 0)      |
| marker = 0                 |
+----------------------------+
| main()                     |
+----------------------------+
```

### Heap

```
(empty)
```

### Explanation

- `local_int`, `local_buf`, and `p_local` are local variables.
- `p_local` stores the address of `local_int`.
- Both variables exist only while `dump_frame()` is executing.

---

## Execution Point 4 – Recursive Calls

Each recursive call creates a new stack frame.

```
dump_frame(depth=3)
↓

walk_stack(depth=3)
↓

dump_frame(depth=2)
↓

walk_stack(depth=2)
↓

dump_frame(depth=1)
↓

walk_stack(depth=1)
↓

dump_frame(depth=0)
↓

walk_stack(depth=0)
↓

main()
```

### Explanation

Each recursive call has:

- its own `marker`
- its own `local_int`
- its own `local_buf`
- its own `p_local`

None of these variables are shared between recursive calls.

The output shows that stack addresses become smaller during recursion, indicating that the stack grows toward lower memory addresses on this system.

---

## Execution Point 5 – Function Return

As recursion unwinds, stack frames are removed in reverse order.

```
depth 3 returns
↓

depth 2 returns
↓

depth 1 returns
↓

depth 0 returns
↓

main returns
```

### Explanation

Each function's local variables are automatically destroyed when that function returns.

---

## Memory Summary

### Stack

- main()
- walk_stack()
- dump_frame()
- marker
- local_int
- local_buf
- p_local

### Heap

No heap memory is allocated because the program never calls `malloc()`, `calloc()`, or `realloc()`.

---

# Program: heap_example.c

## Program Overview

This program demonstrates dynamic memory allocation, ownership, and a deliberate memory leak.

---

## Execution Point 1 – Start of main()

### Stack

```
main()

alice = NULL
bob = NULL
```

### Heap

```
(empty)
```

---

## Execution Point 2 – Creating Alice

After:

```c
alice = person_new("Alice", 30);
```

### Stack

```
alice --------+
bob = NULL    |
```

### Heap

```
Person
|
+--> name ---> "Alice"
|
+--> age = 30
```

### Explanation

Two allocations occur:

1. `Person`
2. Character array storing `"Alice"`

The structure owns the string.

---

## Execution Point 3 – Creating Bob

After:

```c
bob = person_new("Bob", 41);
```

### Stack

```
alice ------+
bob --------+
```

### Heap

```
Person (Alice)
    |
    +--> "Alice"

Person (Bob)
    |
    +--> "Bob"
```

### Explanation

The two objects are completely independent.

---

## Execution Point 4 – Freeing Bob

After:

```c
free(bob->name);
free(bob);
```

### Stack

```
alice --> valid

bob --> dangling pointer
```

### Heap

```
Alice Person
|
+--> Alice

Bob allocation
FREED
```

### Explanation

The memory owned by Bob is correctly released.

The variable `bob` still stores the old address, making it a dangling pointer.

---

## Execution Point 5 – Freeing Alice

The function

```c
person_free_partial(alice);
```

executes:

```c
free(p);
```

only.

### Heap

```
Alice Person
FREED

"Alice"
STILL ALLOCATED
```

### Explanation

The structure is released.

The dynamically allocated string is never freed.

This produces a **memory leak**.

---

## Ownership

- `alice` owns the `Person` object.
- The `Person` object owns `alice->name`.
- Both allocations must be freed separately.

---

## Memory Summary

### Stack

- alice
- bob

### Heap

- Person objects
- Name strings

---

# Program: aliasing_example.c

## Program Overview

This program demonstrates pointer aliasing and use-after-free.

---

## Execution Point 1 – Before Allocation

### Stack

```
main()

a = NULL
b = NULL
n = 5
```

### Heap

```
(empty)
```

---

## Execution Point 2 – After make_numbers()

### Stack

```
a --------+
b = NULL  |
```

### Heap

```
Array

0
11
22
33
44
```

### Explanation

The array is dynamically allocated on the heap.

---

## Execution Point 3 – Pointer Aliasing

After

```c
b = a;
```

### Stack

```
a --------+

           |

b --------+|

           ||

Heap       ||

Array <----+

0
11
22
33
44
```

### Explanation

Both pointers reference the same heap allocation.

No new memory is allocated.

This is called **pointer aliasing**.

---

## Execution Point 4 – Freeing the Allocation

After

```c
free(a);
```

### Stack

```
a --> dangling pointer

b --> dangling pointer
```

### Heap

```
Memory released
```

### Explanation

The allocation no longer exists.

Both pointers still contain the old address.

They are dangling pointers.

---

## Execution Point 5 – Invalid Read

The statement

```c
printf("%d", b[2]);
```

reads from memory that has already been freed.

This is an **invalid read** and **use-after-free**.

---

## Execution Point 6 – Invalid Write

The statement

```c
b[3] = 1234;
```

writes into memory that has already been freed.

This is an **invalid write** and **use-after-free**.

---

## Ownership

Initially, `a` owns the allocated array.

After

```c
b = a;
```

both pointers refer to the same allocation.

After

```c
free(a);
```

neither pointer refers to valid memory.

---

# AI Review

## Example 1

### AI Statement

> Calling `free(ptr)` automatically changes `ptr` to `NULL`.

### Why It Is Incorrect

`free()` releases the memory block but does not modify the pointer variable.

The pointer still contains the old address.

### Correct Explanation

The pointer becomes a **dangling pointer** after `free()`.

It only becomes `NULL` if the programmer explicitly assigns:

```c
ptr = NULL;
```

---

## Example 2

### AI Statement

> Freeing a structure automatically frees every pointer stored inside the structure.

### Why It Is Incorrect

`free()` only releases the memory block passed to it.

It does not automatically free dynamically allocated members.

### Correct Explanation

Each dynamically allocated member must be freed individually before freeing the structure itself.

Otherwise, memory leaks occur.

---

# Overall Conclusions

- Stack variables exist only while their function is executing.
- Heap allocations remain valid until explicitly freed.
- Pointer aliasing means multiple pointers reference the same allocation.
- Freeing memory does not modify existing pointers.
- Accessing freed memory causes undefined behavior.
- Every dynamically allocated object must be released exactly once.
- Ownership determines which part of the program is responsible for calling `free()`.