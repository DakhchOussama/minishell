# Minishell Project

Welcome to the Minishell project! 🐚 This C-based project focuses on creating a simple shell with essential functionalities.

## Project Overview

- **Language:** C
- **Project Structure:**
  - `Makefile`: ⚙ Build automation file.
  - ... (list of other source files)

## Project Structure

The Minishell project is structured with a set of source files. Each file contributes to the implementation of specific functionalities:

- `main.c`: 🚀 Main entry point for the Minishell.
- `minishell.h`: 📜 Header file containing function prototypes and definitions.
- `check_env_var.c`: 🌐 Implementation of checking environment variables.
- `error.c`: ⚠ Error handling implementation.
- `execut.c`: 💻 Execution-related functions.
- ... (and others)

## Project Guidelines

Here are the key guidelines and requirements for the Minishell project:

### General Requirements

1. Display a prompt when waiting for a new command.
2. Implement a working history feature.
3. Search and launch the right executable based on the PATH variable or using a relative or absolute path.
4. Use a single global variable to indicate a received signal, limiting its access and data scope.

### Command Interpretation

5. Do not interpret unclosed quotes or special characters unnecessary for the subject, such as \ (backslash) or ; (semicolon).
6. Handle single quotes (') to prevent interpreting metacharacters in the quoted sequence.
7. Handle double quotes (") to prevent interpreting metacharacters, except for $ (dollar sign).

### Redirections and Pipes

8. Implement redirections:
   - `<` should redirect input.
   - `>` should redirect output.
   - `<<` should read input until a line with a specified delimiter is seen.
   - `>>` should redirect output in append mode.
9. Implement pipes (`|` character) to connect the output of each command in the pipeline to the input of the next command.

### Environment Variables

10. Handle environment variables (`$` followed by a sequence of characters) and expand them to their values.
11. Handle `$?`, which should expand to the exit status of the most recently executed foreground pipeline.

### Interactive Mode

12. Handle ctrl-C, ctrl-D, and ctrl-\ as follows in interactive mode:
    - ctrl-C displays a new prompt on a new line.
    - ctrl-D exits the shell.
    - ctrl-\ does nothing.

### Builtins

13. Implement the following builtins:
    - `echo` with the option `-n`.
    - `cd` with only a relative or absolute path.
    - `pwd` with no options.
    - `export` with no options.
    - `unset` with no options.
    - `env` with no options or arguments.
    - `exit` with no options.

### Readline Function

14. The `readline()` function can cause memory leaks. Your code must not have memory leaks.

## 42 Network

This project is part of the 42 Network, an innovative and peer-to-peer learning platform. To learn more about the 42 Network, visit [42 Network](https://www.42.fr/42-network/).

## How to Use 🚀

1. Clone the repository to your local machine.
2. Navigate to the project folder.
3. Build the project using the provided Makefile.
   ```bash
   $ make
   ```
### Run the Minishell
```
  ./minishell
```
