# C Projects

A collection of standalone C projects for learning the C programming language. Each project is located in the `projects/` directory with its own `makefile` for building. The code largely follows C11 standards.

## Projects

### Basics

- **[Hello World](projects/basics/hello_world/)**: A simple program that prints "Hello, World!" to the console.

### Games

- **[Battle](projects/games/battle)**: A command-line turn-based RPG game.
- **[Uno](projects/games/uno/)**: A command-line implementation of the Uno card game.

## Compilation

Each project contains a `makefile`. To compile a project, navigate to its directory and run:

```bash
make
```

This will generate an executable file in the same directory. The main compiler used is `gcc`, and the code adheres to C11 standards.

Every project is self-contained, so dependencies are managed within each project's directory.
