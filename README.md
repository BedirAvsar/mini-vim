# Mini-Vim

Mini-Vim is a small terminal-based text editor written in C.

This project was created as a learning exercise to understand how text editors
work internally, especially at a low level where the program directly interacts
with the terminal and the operating system.

Mini-Vim is not intended to be a full-featured editor like Vim or Nano.
Instead, it focuses on building a clean and understandable editor core.

---

## Why This Project Exists

Modern text editors hide many important details behind libraries and frameworks.
As a junior developer, I wanted to understand:

- How a terminal really handles keyboard input
- How editors react instantly to key presses
- How text is stored and managed in memory
- How the screen is manually redrawn without GUI libraries

This project answers those questions by implementing everything step by step,
using only standard C and system calls.

---

## What This Project Does

Mini-Vim implements the core building blocks of a text editor:

- Switches the terminal into raw mode to read input immediately
- Reads keyboard input byte by byte
- Handles special keys like arrow keys and control combinations
- Stores text in a dynamic row-based buffer
- Draws the editor screen using ANSI escape codes
- Manages cursor position and editor state

The goal is not feature completeness, but clarity and correctness.

---

## How It Works (High Level)

1. The editor switches the terminal into raw mode
2. Key presses are read directly from standard input
3. Each key press updates the editor state (cursor position or text)
4. The screen is cleared and redrawn on every update
5. The cursor is repositioned based on the current state

This loop continues until the user exits the editor.

---

## Real-World Relevance

This project helped me understand concepts that are used in real systems:

- Terminal-based tools and editors
- Event-driven programs
- Low-level input/output
- Memory management in C
- Separation of responsibilities in multi-file projects

These ideas apply not only to editors, but also to debuggers, shells, and other
system-level software.

---

## Project Structure

```text
mini-vim/
├── include/
│   ├── editor.h    # Editor state and core functions
│   ├── input.h     # Keyboard input handling
│   ├── buffer.h    # Text buffer and rows
│   └── syntax.h    # Planned (future feature)
├── src/
│   ├── main.c
│   ├── editor.c
│   ├── input.c
│   └── buffer.c
├── tests/
├── Makefile
└── README.md

## Build and Run

Requirements:
	•	GCC or Clang
	•	Unix-based system (Linux / macOS)

Build the project:
make

Run the editor:
./mini-vim

Exit the editor with:
Ctrl - X


⸻

Current Status

This project represents Mini-Vim v1.

The core editor functionality is complete.
Additional features such as file saving, scrolling, and syntax highlighting
can be added in future versions.

⸻

What I Learned
	•	How terminals work in raw mode
	•	How editors process keyboard input
	•	How text editors manage internal state
	•	How to structure a medium-sized C project
	•	How to work closer to the operating system
