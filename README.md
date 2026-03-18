# Mini-Vim CLI  
*A minimal terminal-based text editor written in C with raw terminal control and dynamic buffer management.*

![C](https://img.shields.io/badge/C-Programming-blue)
![POSIX](https://img.shields.io/badge/POSIX-Terminal-green)
![Docker](https://img.shields.io/badge/Docker-Containerized-blue)
![Build](https://img.shields.io/badge/Build-Makefile-orange)

---

## The 'Why' & Real-World Use Case

Modern text editors abstract away low-level system interactions through high-level libraries and frameworks. This project demonstrates how a text editor can be built from scratch using direct terminal and OS-level control.

Mini-Vim CLI focuses on solving real-time input handling, terminal rendering, and memory management challenges. These concepts are directly applicable to building shells, debuggers, terminal tools, and other system-level applications.

---

## Architecture & Technical Decisions

- **Event-Driven Architecture**
  - Continuous loop: read input → update state → render screen

- **Raw Terminal Control (termios)**
  - Disables canonical mode, echo, and signals
  - Enables byte-level input handling

- **Dynamic Text Buffer**
  - Custom `erow` struct
  - Uses `malloc` / `realloc` for growth

- **Rendering Engine**
  - ANSI escape sequences
  - Full screen redraw per keypress

- **Separation of Concerns**
  - `editor.c` → core logic
  - `input.c` → key handling
  - `buffer.c` → data layer

---

## Tech Stack

- C
- POSIX (termios, low-level I/O)
- Makefile
- Docker (multi-stage Alpine build)

---

## Getting Started

### Clone
```bash
git clone https://github.com/BedirAvsar/mini-vim_cli.git
cd mini-vim_cli
```

### Build
```bash
make
```

### Run
```bash
./mini-vim
```

### Exit
```
CTRL + X
```

---

### Run with Docker

```bash
docker build -t mini-vim .
docker run -it mini-vim
```

---

## Usage

### Controls

| Action | Key |
|------|-----|
| Move Cursor | Arrow Keys |
| Exit | CTRL + X |
| Insert Text | Type |

### Example

```bash
./mini-vim
```

---

## What I Learned

- Low-level terminal I/O with `termios`
- Dynamic memory management in C
- Event-driven architecture design
- ANSI escape-based rendering
- Modular C project structuring

### Biggest Challenge

Handling raw input and decoding multi-byte escape sequences (especially arrow keys) correctly without libraries.
