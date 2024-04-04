# Protocol Scope Script

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
: ~ = sets the value of where the pointer is to the position of the pointer
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

### +
The `+` command adds 1 to the memory adress that the pointer is at. For example to have an array position with the value 3 you would do `1'1:+++`. This would add 1 three times to the pointer position of the array and make it equal to 3. The pseudo code equivelent to this would be:
```pseudo
int memory[1][1]; // initialize
memory[0][0]+=1; // +
memory[0][0]+=1; // +
memory[0][0]+=1; // +
```

---

### -
Similarly, the `-` command subtracts 1 from a memory adress that the pointer is at. For example you have a array position with the value of 2 and you subract 2 to make it equal to 0: `1'1:++--`. This would add 2 to the array but after would subract 1 two times, making it equal to 0. The pseudo code equivelent to this would be:
```
int memory[1][1]; // initialize
memory[0][0]+=1; // +
memory[0][0]+=1; // +
memory[0][0]-=1; // -
memory[0][0]-=1; // -
```

---
