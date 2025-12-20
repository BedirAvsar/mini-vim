# Mini-Vim

A minimal, terminal-based text editor written in C.

## Project Objective
This project is a technical study in systems programming. The goal is to build a functional text editor from scratch without relying on high-level UI libraries like `ncurses`. It interacts directly with the Linux kernel via standard POSIX terminal interfaces.

## Technical Scope
- **Language:** C (C99 standard)
- **Dependencies:** None (Standard C Library & POSIX only)
- **Core Concepts:**
  - **Terminal Manipulation:** Transitioning from canonical mode to raw mode using `termios` structs.
  - **Input Handling:** Processing individual byte streams and escape sequences.
  - **Memory Management:** Manual allocation for row/buffer structures.

## Implementation Details
The editor modifies terminal attributes (`c_lflag`, `c_iflag`) to disable default processing (echo, canonical mode, signal shortcuts). It ensures the terminal state is restored upon program exit using `atexit()` handlers to prevent shell corruption.

## Acknowledgement
This project is based on the [Build Your Own Text Editor](https://viewsourcecode.org/snaptoken/kilo/) guide by **antirez**. The code logic follows the tutorial but has been refactored and commented to reinforce my understanding of the underlying system calls.
