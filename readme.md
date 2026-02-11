<div align=center>
    <h1>mcc89</h1>
</div>

## about

`mcc89` (`matyz's C89 Compiler`) is C89 compiler written in C89 that compiles down to x86-64 assembly (currently only my [pasm-x86](https://github.com/Matissoss/pasm) assembler).

## building project

Run:
```sh
just build
```

Or:
```sh
cc src/*.c -o mcc89 -std=c89 -pedantic -Wall -Werror
```

## development roadmap

### v0.1

Goals:
- Support primitive data types (`int`, `char`, `void`, `long`, pointers, etc.)
- Full compilation process
- Emiting x86-64 assembly

Tasks:
- [ ] Tokenizer
- [ ] Lexer
- [ ] Parser
- [ ] Checker
- [ ] Conversion into IR
- [ ] Converting IR into x86-64 assembly

### v0.2

Goals:
- Support for `static`s
- Support for `struct`s, `enum`s, `union`s
- Support more complex types (such as `int *(*t[3])(char)`)
- Support for preprocessor's directives (`#include`, `#ifdef`, `#ifndef`, `#define`, etc.) 
- Allow compiler to finally make use of system's `libc`

### v0.3
Goals:
- First simple optimizations
- TBD

## credits

`mcc89` is brought to you by matyz,

licensed under MPL 2.0
