# Brainfuck-Compiler
Brainfuck is an [esoteric programming language](https://en.wikipedia.org/wiki/Esoteric_programming_language "wiki") created in 1993 by Urban Müller.

Notable for its extreme minimalism, the language consists of only eight simple commands, a [data pointer](https://en.wikipedia.org/wiki/Data_pointer "wiki") and an [instruction pointer](https://en.wikipedia.org/wiki/Instruction_pointer "wiki"). While it is fully [Turing complete](https://en.wikipedia.org/wiki/Turing_completeness "wiki"), it is not intended for practical use, but to challenge and amuse [programmers](https://en.wikipedia.org/wiki/Programmers "wiki"). Brainfuck requires one to break commands into microscopic steps.

The language's name is a reference to the slang term [brainfuck](https://en.wiktionary.org/wiki/brainfuck "wiki"), which refers to things so complicated or unusual that they exceed the limits of one's understanding, as it was not meant or made for designing actual software but to challenge the boundaries of [computer programming](https://en.wikipedia.org/wiki/Computer_programming "wiki").

## Build
```bash
g++ -o brainfuck main.cpp brainfuck.cpp
```

## Usage
```bash
./brainfuck example/hello_world.bf
```

## Language Design
The language consists of eight [commands](https://en.wikipedia.org/wiki/Command_(computing) "wiki"). A brainfuck program is a sequence of these commands, possibly interspersed with other characters (which are ignored). The commands are executed sequentially, with some exceptions: an [instruction pointer](https://en.wikipedia.org/wiki/Program_Counter "wiki") begins at the first command, and each command it points to is executed, after which it normally moves forward to the next command. The program terminates when the instruction pointer moves past the last command.

The brainfuck language uses a simple machine model consisting of the program and instruction pointer, as well as a one-dimensional array of at least 30,000 [byte](https://en.wikipedia.org/wiki/Byte "wiki") cells initialized to zero; a movable [data pointer](https://en.wikipedia.org/wiki/Pointer_(computer_programming) "wiki") (initialized to point to the leftmost byte of the array); and two streams of bytes for input and output (most often connected to a keyboard and a monitor respectively, and using the [ASCII](https://en.wikipedia.org/wiki/ASCII "wiki") character encoding).

The eight language commands each consist of a single character:
|Character| Meaning |
|  :---:  |  :---   |
| `>` | Increment the data pointer by one (to point to the next cell to the right). |
| `<` | Decrement the data pointer by one (to point to the next cell to the left). |
| `+` | Increment the byte at the data pointer by one. |
| `-` | Decrement the byte at the data pointer by one. |
| `.` | Output the byte at the data pointer. |
| `,` | Accept one byte of input, storing its value in the byte at the data pointer. |
| `[` | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching `]` command. |
| `]` | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching `[` command. |

`[` and `]` match as parentheses usually do: each `[` matches exactly one `]` and vice versa, the `[` comes first, and there can be no unmatched `[` or `]` between the two.

As the name suggests, Brainfuck programs tend to be difficult to comprehend. This is partly because any mildly complex task requires a long sequence of commands and partly because the program's text gives no direct indications of the program's [state](https://en.wikipedia.org/wiki/State_(computer_science) "wiki"). These, as well as Brainfuck's inefficiency and its limited input/output capabilities, are some of the reasons it is not used for serious programming. Nonetheless, like any Turing complete language, Brainfuck is theoretically capable of computing any computable function or simulating any other computational model, if given access to an unlimited amount of memory. A variety of Brainfuck programs have been written. Although Brainfuck programs, especially complicated ones, are difficult to write, it is quite trivial to write an interpreter for Brainfuck in a more typical language such as C due to its simplicity. There even exist Brainfuck interpreters written in the Brainfuck language itself.

Brainfuck is an example of a so-called [Turing tarpit](https://en.wikipedia.org/wiki/Turing_tarpit "wiki"): It can be used to write any program, but it is not practical to do so, because Brainfuck provides so little abstraction that the programs get very long or complicated. 