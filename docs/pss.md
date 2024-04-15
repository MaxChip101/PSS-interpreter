## Introduction

Protocol Scope Script (pss) is a simplifiefd programming language with the syntax: `+-<>?!_()[]&*~;@`
pss is similar to brainfuck in it's syntax but has a couple more functions built into it. The interpreter works by iterating through the characters of the script, and reading what each character is. Every letter besides prefix characters in some cases will be ignored as comments.

---

## Basics

The bascics behind pss is similar to brainfuck, which is memory manipulation. The memory in pss is an array with set bounds you create, you would start your script with: `{array_size}^{scope_count}:`. This would tell the interpreter how big your array should be. Pss has 15 functions which are:
```pss
 @     comment
 +     increases the number of where the pointer is by 1
 -     decreases the number of where the pointer is by 1
 <     moves the pointer to the left of the array by 1
 >     moves the pointer to the right of the array by 1
 [     begins a loop
 ]     ends a loop
 (     begins a scope
 )     ends a scope
 &     sets the value of where the pointer is to the position of the pointer
 *     gets the value of a position on the array
 ~     goes to the position that the pointer value is equal to
 _     copies the value of where the pointer is and pastes it where it is told
 ?     sets the value of where the pointer is to the user input
 !     prints the value of where the pointer is
 ;     sleeps for the a set amount of milliseconds
 $     makes, writes, and reads files
```

---

### Some rules for the syntax:

> - loops can be nested in each other

> - the pointer starts at 0 which is the very left of the memory array

> - scope size is how many scopes will be the maximum amount of scopes that are nested in each other: `( - 1 scope (2 - scopes (3 - scopes)))`

> - comments have to be sandwiched like `@ comment @`

---

## Syntax

This section is going to describe how to use the syntax in pss and how it works

### Structure

The structure of the code is pretty simple. How you strucure the code is dependent on how big of an array and how many scopes your script needs. You would strucure your code like this: `{array_size}^{scope_count}:`. For example if you take 16 memory slots and have 2 scopes in use then you would strucure the code like this `16^2:`. The single quotation mark seperates the size of your array from your scope size, the colon ends the preset and any character after the colon is seen as code.

---

### Comments
The `@` command would initiate a comment that would make the interpreter ignore any syntax inside the comment. The comment could be ended by placing another `@` command.
This is similar to `/**/` kind of comment system in C. Here is an example: `1^1: @ Hello, World! @` this would not do anything since the the only syntax which is a `!` is within a comment that would make it not be read by the interpreter.

---

### Value Manipulation
The `+` command adds 1 to the memory address that the pointer is at. Similarly, the `-` command subtracts 1 from a memory address that the pointer is at. For example you have a array position with the value of 2 and you subract 2 to make it equal to 0: `1^1:++--`. This would add 2 to the array but after would subract 1 two times, making it equal to 0. The pseudo code equivelent to this would be:
```c
int memory[1][1]; // initialize
memory[0][0]+=1; // +
memory[0][0]+=1; // +
memory[0][0]-=1; // -
memory[0][0]-=1; // -
```

---


### Pointer Control
The `<` command moves the pointer left by 1 index. Similarly the `>` command moves the pointer right by 1 index. These can be used to move across the memory array that you start off with. Here is an example: `6^1:++>+++>+<<-`. This would add 2 to position 0 and move right then add 3 to position 1 and move right to add 1 to position 2 and go left by two to subract by 1. Here is the code in pseudo code:
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
The `[` command starts a loop at the character position and it would loop back the value of the pointer that was there before the loop began. The `]` command would tell the interpreter to loop back to the position of the beginning of the loop. For example: `2^1:+++[>++<-]`. This would add 3 to position 0 and would loop 3 times adding 2 to position 1 and position 0 having a value of 0. Here is the code in pseudo code:
```c
int memory[1][2]; // initialize
int pointer; // initialize
int loop_position;
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
loop_position = pointer;
while(memory[0][loop_position] != 0) { // [
    scope++; // >
    memory[0][pointer]+=1; // +
    memory[0][pointer]+=1; // +
    scope--; // <
    memory[0][pointer]-=1; // -
} // ]
```

---

### Scopes
The `(` command would start a scope which would copy every single element from the previous scope into the new one and would put the pointer in the new scope. Anything that you change in the scope will not affect anything outside of it. The `)` command would end a scope which would delete everything in the new scope and put the pointer in the previous scope. Here is an example: `1^2:+++(++)`. This code will add 3 to position 0 then create a new scope, then in the new scope, add 2, then the scope ends. This in the end will equal 3 because the 2 added to the new scope did not affect the previous scope. Here is pseudo code for it:
```c
int memory[2][1]; // initialize
int scope = 0; // initialize
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
The `_` command would get the value of the pointer position on the memory array and would copy it then anything in between the 2 `_` would act as directions to tell the interpreter where to paste the value. Here is an example: `3^1:+++_>>_`. This code would add 3 to position 0 and would copy it and paste it to the position 2. Here is pseudo code of how it works:
```c
int memory[1][3]; // initialize
int pointer=0; // initialize
int copy_value; // initialize
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
memory[0][pointer]+=1; // +
copy_value = memory[0][pointer]; // _
pointer++; // >
pointer++; // >
memory[0][pointer] = copy_value; // _
```

---

### Pointer Setting
The `&` command sets the value of the pointer to the pointer position. The `*` command gets the value of a position on the memory array that the pointer value is equal to. The `~` command sets the position of the pointer to the value of the pointer. For example: `3^1:>>&_<<_~<<*`. What is happening in this script is that the pointer goes right by 2 positions, and gets the pointer position and then copies it back 2 positions and then the pointer goes to the position 2. Here is pseudo code of how it works:
```c
int memory[1][3]; // initialize
int pointer=0; // initialize
int copy_value; // initialize
pointer++; // >
pointer++; // >
memory[0][pointer] = pointer; // &
copy_value = memory[0][pointer]; // _
pointer--; // <
pointer--; // <
memory[0][pointer] = copy_value; // _
pointer = memory[0][pointer]; // ~
pointer--; // <
pointer--; // <
memory[0][pointer] = memory[0][memory[0][pointer]]; // *
```

---

### Input And Output

The `!` command would print the value of the pointer to the console. The `?` command would set the value of the pointer to the input number from the console. The prefixs for printing is `c, n, s`. `c` turn the output valure into a char. `n` creates a new line. `s` creates a white space. for input, the only prefix is `c` which would turn the input type into a character. Prefixs are put before a command like `c!` which would print the ASCII value of the pointer value, while `c?` would recieve a character and turn it into the ASCII value of that character. For example: `1^1:?c!`. This code gets the ASCII value of b which is 98 and prints the ASCII character of 98. Here is the pseudo code of how it works:
```c
int memory[1][1]; // initialize
memory[0][0] = getline(int); // ?
printchar(memory[0][0]); // c!
```

An example for input is: `1^1:c?!`. this would get the input character and save it to the pointer value, then it would print the ASCII code of the pointer position. Here is pseudo code of how it works:
```c
int memory[1][1]; // initialize
memory[0][0] = getline(char); // c?
printint(memory[0][0]); // !
```

---

### Sleep

The `;` command would sleep for the value of the pointer milliseconds. An example for this would be `1^1:++++++++++[++++++++++]--------------------[++++++++++]++++++++++;!`. This would wait 1000 milliseconds or 1 second before printing the value of the pointer. Here is the pseudo code of how it works:
```c
int memory[1][1]; // initialize
memory[0][0] += 1000; // +
sleep(memory[0][0]); // ;
printint(memory[0][0]); // !
```

---

### Files

In progress...

## Examples

### 1 - Adding calculator
```pss
4^1:
+++++++++++++++++++++++++++++++++++++++++++ @ 43 plus + @
>
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ @ 58 colon : @
>
+!<c!>>s!? @ input 1 @
<<<c!n!>>> @ print plus @
>
<<+!<c!>>>s!? @ input 2 @
[
    <+>- @ addition @
]
<! @ output @
```
input 1: `10`
input 2: `12`
output: `22`

### 2 - ASCII character offset
```pss
1^1:c?++c!
```
input: `a`
output: `c`
