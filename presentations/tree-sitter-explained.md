---
title: Tree-sitter Explained
author: teej_dv
date: 2024-03-08
---

# Video

 ![tree-sitter explained](https://youtu.be/09-9LltqWLY)
# Tree-sitter

# STOOOOOOOOOOOOOOOOOOOOOP

If you're thinking:

> "wOw nOw i'lL kNoW EvErYtHiNg aBoUt lSp tOo" <!-- stop -->

**NO!**

# Tree-sitter Is NOT

- Language Server Protocol (LSP) <!-- stop -->
- A Compiler <!-- stop -->
- An Interpreter

# Tree-sitter Is

- Parser generator tool <!-- stop -->
- Incremental parsing library <!-- stop -->
- A query engine (more on this later)

# Tree-sitter Is

A "framework" to:
- Generate a syntax tree
- Ask questions about the tree

# Why Tree-sitter (In An Editor)

- Editors that use tree-sitter:
  - Neovim (BTW)
  - Helix
  - Zed
  - Emacs
  - (Maybe more?)

# Why Tree-sitter (In An Editor)

- Incremental
- Error Recovery
<!-- Also very important. Not just because you mostly write broken code,
    but as you're writing the code is mostly broken.
    It's only not broken when you're finished writing. -->
- Queries

# How Does Tree-sitter Work?

# Underlying Stack: `grammar.js`

- Grammars are written in "javascript" <!-- stop -->
  - You write them in javascript, but more correctly "A Javascript-like DSL".
    - `grammar.js` <!-- stop -->
  - These are compiled to `parser.c` via the tree-sitter cli

# Underlying Stack: Results of `grammar.js`

```
├── src
│   ├── grammar.json
│   ├── node-types.json
│   ├── parser.c
│   ├── scanner.c
│   └── tree_sitter
│       └── parser.h
```

#  Why C (since it's outdated & illegal)?

- Only dependencies is a C Compiler
- Good FFI story for lots of languages

This results in tree-sitter being very portable

# Then what?

Compile the C code to a shared library!

```
$ cc -o ./build/parser.so -I./src src/parser.c src/scanner.c -shared -Os -fPIC
```

# After compiling, then what?

Now you have:

```
$ ls -al build
total 304
drwxrwxr-x tjdevries   4096 ./
drwxrwxr-x tjdevries   4096 ../
-rwxrwxr-x tjdevries 299680 parser.so*
```

# Shared Library

You can load that shared library as a parser inside of some application
that supports tree-sitter.

In this case, we'll use Neovim to explore and show some of what tree-sitter is doing.

# Exploring Tree-sitter

*NOTE*: Some of you may be triggered. I'm about to show you `lisp` code.
- Consider this your final warning <!-- stop -->
- Also, `scheme` is cool :)

# Exploring Tree-sitter

> Open `example.go` file

# What is Tree-sitter Used For (In An Editor)?

- Highlighting
  - Embedding Languages
- Indenting <!-- stop -->
- Structural Editing
  - Text Objects (`daf` -> `d`elete `a`round `f`unction)
  - Selection
  - Move <!-- stop -->
- Code Context <!-- stop -->
- Folding <!-- stop -->
- ...

# What is Tree-sitter Used For (Outside Editors)?

- Code Analysis
- Code Linter
- Code Highlighting

# Conclusion
