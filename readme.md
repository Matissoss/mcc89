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
cc src/*.c -o mcc89 --std=c89
```

## development roadmap

### v0.1

Goals:
- Support primitive data types (`int`, `char`, `void`, `long`, pointers, etc.)
- Full compilation process
- Emiting x86-64 assembly

- [ ] Tokenizer
- [ ] Lexer
- [ ] Merger (converting Lexer tokens into AST)
- [ ] Checker
- [ ] Converting code into x86-64 assembly

### v0.2

TBD

## credits

`mcc89` is brought to you by matyz,

licensed under MPL 2.0
