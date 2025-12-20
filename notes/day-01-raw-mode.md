# Day 1: Terminal Raw Mode Implementation

## Objective
The primary goal of this phase was to transition the terminal interface from its default "Canonical Mode" to "Raw Mode." Standard input handling (`stdio.h` functions or default `read` behavior) buffers input until the Enter key is pressed, which is unsuitable for a real-time text editor that requires character-level control.

## Technical Implementation

### 1. Disabling Canonical Mode
By default, terminals operate in canonical mode, where input is processed line-by-line. To enable immediate response to key presses, the `termios` library was used to modify terminal attributes.
- **Action:** Disabled the `ICANON` flag.
- **Reason:** To force the `read()` system call to return as soon as a single byte is received, rather than waiting for a newline character.

### 2. Disabling Echo
- **Action:** Disabled the `ECHO` flag.
- **Reason:** In a text editor, the program—not the terminal—should control what is rendered on the screen. This prevents the user's keystrokes from being printed automatically, allowing for custom rendering logic later.

### 3. Signal and Flow Control Management
Several default terminal behaviors interfere with the functionality of a text editor:
- **`ISIG`:** Disabled to prevent `Ctrl-C` (SIGINT) and `Ctrl-Z` (SIGTSTP) from terminating or suspending the process directly. These signals will be handled programmatically.
- **`IXON`:** Disabled software flow control (XOFF/XON) to reclaim `Ctrl-S` and `Ctrl-Q` for editor shortcuts.
- **`ICRNL`:** Disabled the translation of Carriage Return (`\r`) to Newline (`\n`) to handle input raw values accurately.

### 4. Restoration of Terminal State
Modifying terminal attributes is a stateful operation that persists after program termination. If the program crashes or exits without resetting these attributes, the user's shell becomes unusable.
- **Solution:** Implemented `disableRawMode()` and registered it with `atexit()`.
- **Reason:** Ensures that the original terminal attributes are automatically restored upon program exit, regardless of where or how the termination occurs.

## Key Takeaways
This session focused on understanding POSIX terminal interfaces via `struct termios`. The implementation required low-level bitwise operations to mask specific flags, highlighting the difference between high-level input abstraction and direct system manipulation.