## Introduction

Protocol Scope Script (pss) is a simplifiefd programming language with the syntax: `+-<>,.c|()[]`
pss is similar to brainfuck in it's syntax but has a couple more functions built into it. The interpreter works by iterating through the characters of the script, and reading what each character is. Every letter besides `c` in some cases will be ignored as comments.

---

## Basics

The bascics behind pss is similar to brainfuck, which is memory manipulation. The memory in pss is an array with set bounds you create, you would start your script with: `{array_size}'{scope_count}:`. This would tell the interpreter how big your array should be. Pss has 12 functions which are:
```brainfuck
: + = increases the number of where the pointer is by 1
: - = decreases the number of where the pointer is by 1
: < = moves the pointer to the left of the array by 1
: > = moves the pointer to the right of the array by 1
: [ = begins a loop
: ] = ends a loop
: ( = begins a scope
: ) = ends a scope
: @ = sets the value of where the pointer is to the position of the pointer
: ~ = goes to the position that the pointer value is equal to
: | = copies the value of where the pointer is and pastes it where it is told
: , = sets the value of where the pointer is to the user input
: . = prints the value of where the pointer is
: c = changes the input or print type to a character

```

---

### Some rules for the syntax:

> - loops cannot be nested in each other

> - `c` goes before a `,` or `.` to function

> - `|` is structered like `|{code}|`

> - the pointer starts at 0 which is the very left of the memory array

---

## Syntax

This section is going to describe how to use the syntax in pss and how it works

### Structure

The structure of the code is pretty simple. How you strucure the code is dependent on how big of an array and how many scopes your script needs. You would strucure your code like this: `{array_size}'{scope_count}:`. For example if you take 16 memory slots and have 2 scopes in use then you would strucure the code like this `16'2:`. The single quotation mark seperates the size of your array from your scope size, the colon ends the preset and any character after the colon is seen as code.

---

### Value Manipulation
The `+` command adds 1 to the memory address that the pointer is at. Similarly, the `-` command subtracts 1 from a memory address that the pointer is at. For example you have a array position with the value of 2 and you subract 2 to make it equal to 0: `1'1:++--`. This would add 2 to the array but after would subract 1 two times, making it equal to 0. The pseudo code equivelent to this would be:
```c
int memory[1][1]; // initialize
memory[0][0]+=1; // +
memory[0][0]+=1; // +
memory[0][0]-=1; // -
memory[0][0]-=1; // -
```

---


### Pointer Control
The `<` command moves the pointer left by 1 index. Similarly the `>` command moves the pointer right by 1 index. These can be used to move across the memory array that you start off with. Here is an example: `6'1:++>+++>+<<-`. This would add 2 to position 0 and move right then add 3 to position 1 and move right to add 1 to position 2 and go left by two to subract by 1. Here is the code in pseudo code:
```c
int memory[1][6]; // initialize
int pointer=0; // initialize
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
pointer++; // >
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
pointer++; // >
memory[0][pointer]+=1; // +
pointer--; // <
pointer--; // <
memory[0][pointer]-=1; // -
```

---

### Loops
The `[` command starts a loop at the character position and it would loop back the value of the pointer that was there before the loop began. The `]` command would tell the interpreter to loop back to the position of the beginning of the loop and would subract 1 from the loop count. For example: `1'1:+++[+++]`. This would add 3 to position 0 and would loop 3 times adding 3 to position 0. Here is the code in pseudo code:
```c
int memory[1][1]; // initialize
int loop_count;
memory[0][0]+=1; // +
memory[0][0]+=1; // +
memory[0][0]+=1; // +
loop_count = memory[0][0]; // [
while(loop_count != 0) { // []
    memory[0][0]+=1; // +
    memory[0][0]+=1; // +
    memory[0][0]+=1; // +
} // ]
```

---

### Scopes
The `(` command would start a scope which would copy every single element from the previous scope into the new one and would put the pointer in the new scope. Anything that you change in the scope will not affect anything outside of it. The `)` command would end a scope which would delete everything in the new scope and put the pointer in the previous scope. Here is an example: `1'2:+++(++)`. This code will add 3 to position 0 then create a new scope, then in the new scope, add 2, then the scope ends. This in the end will equal 3 because the 2 added to the new scope did not affect the previous scope. Here is pseudo code for it:
```c
int memory[2][1]; // initialize
int scope = 0;
memory[scope][0]+=1; // +
memory[scope][0]+=1; // +
memory[scope][0]+=1; // +
scope++; // (
memory[scope] = memory[scope-1]; // (
memory[scope][0]+=1; // +
memory[scope][0]+=1; // +
scope--; // )
memory[scope+1] = null; // )
```

---

### Copy And Paste
The `|` command would get the value of the pointer position on the memory array and would copy it then anything in between the 2 `|` would act as directions to tell the interpreter where to paste the value. Here is an example: `3'1:+++|>>|`. This code would add 3 to position 0 and would copy it and paste it to the position 2. Here is pseudo code of how it works:
```c
int memory[1][3]; // initialize
int pointer=0;
int copy_value;
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
copy_value = memory[0][pointer]; // |
pointer++; // >
pointer++; // >
memory[0][pointer] = copy_value; // |
```

