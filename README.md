*This project has been created as part of the 42 curriculum by kjolly and tzara*

# Minishell - As beautiful as a shell

## Description:
Minishell is a 42 school project that consists of creating a simplified shell, mimicking the behavior of Bash. This project is a deep dive into how an operating system manages processes, file descriptors, and system calls.

The challenge lies in building a robust program that can parse user input, handle environment variables, and execute commands while maintaining a clean memory state.

## Instruction:
### Prerequisites
A C compiler (GCC or Clang).
The Readline library (commonly used for history and line editing).

### Step 1: Compilation
This project is writen in C, you can compil it with the makefile at the root of the repository:
bash : make

### Step 2: Execution
the makefile create an executable file so now you can lauch minishell in your terminal.
bash: ./minishell

### Step 3: Test
You can use Minishell just like a standard terminal. Try combining features:

minishell> ls -l | grep "txt" > output.txt
minishell> export MY_VAR=42
minishell> echo $MY_VAR
minishell> cat << END

## Ressources:
https://www.datarockstars.ai/quest-ce-que-le-shell-bash-et-pourquoi-est-il-si-important-pour-linux/
https://doc.ubuntu-fr.org/bash
peer-learning : constant exchange with 42 peers to solve edge cases.
man bash, man fork, man pipe, man execve.

## Technical Features:
The project implements a complete execution pipeline:

* Lexer & Parser: Tokenization of the input string to identify commands, arguments, pipes, and redirections.
* Process Management: Proper use of **fork()**, **waitpid()**, and **execve()** to run commands.
* Signals Handling: Management of ctrl-C, ctrl-D, and ctrl-\ to match Bash's behavior.
* Pipes (|): Implementation of inter-process communication using pipe().
* Redirections: Handling of <, >, << (heredoc), and >>.
* Built-ins: Recoding essential commands: echo, cd, pwd, export, unset, env, and exit.
* Environment Variables: Manual management of the environment linked-list.

## Use of IA
* Help visualize the logic of parsing.
* Debug specific edge cases in the recursive parser.
* Understand complex signal behaviors in interactive vs. non-interactive modes.
