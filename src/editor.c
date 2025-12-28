// Project File
#include "editor.h"
#include "input.h"
#include "buffer.h"

// System libraries
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

/*
 * Store terminal settings before the editor started
 * Editör başlamadan önceki terminal ayarlarını saklar
 */
static struct termios orig_termios;

/*
 * Global editor state
 * Global editör durumu
 */
struct editorState E;

// Print error and exit
// Hata yazdırır ve programdan çıkar
static void die(const char *s) {
    perror(s);
    exit(1);
}

// Restore terminal to original state
// Terminali eski haline döndürür
static void disableRawMode(void) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
        die("tcsetattr");
    }
}

// Enable raw mode
// Terminali raw mode'a alır
static void enableRawMode(void) {
    struct termios raw = orig_termios;

    // Local flags
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

    // Input flags
    raw.c_iflag &= ~(IXON | ICRNL);

    // Output flags
    raw.c_oflag &= ~(OPOST);

    // Control flags
    raw.c_cflag |= CS8;

    // Read timeout
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        die("tcsetattr");
    }
}

// Get terminal window size
// Terminal pencere boyutunu alır
static int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        return -1;
    }

    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;
}

// Initialize editor
// Editörü başlatır
void editorInit(void) {
    // Initialize cursor position
    // İmleci (0,0) konumuna al
    E.cx = 0;
    E.cy = 0;

    // Get terminal size
    // Terminal boyutlarını al
    if (getWindowSize(&E.screenrows, &E.screencols) == -1) {
        die("getWindowSize");
    }

    // Save terminal state
    // Terminal ayarlarını kaydet
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        die("tcgetattr");
    }

    bufferInit();
    bufferAppendRow("Mini-Vim", 8);
    bufferAppendRow("Type something...", 17);

    atexit(disableRawMode);
    enableRawMode();
}

// Refresh the entire screen
// Tüm ekranı yeniden çizer
void editorRefreshScreen(void) {
    // Clear screen
    write(STDOUT_FILENO, "\x1b[2J", 4);

    // Cursor to top-left
    write(STDOUT_FILENO, "\x1b[H", 3);

    // Draw rows
    bufferDrawRows();

    // Position cursor
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
    write(STDOUT_FILENO, buf, strlen(buf));
}

// Process a single keypress
// Bir tuş basımını işler
void editorProcessKeypress(int key) {
    switch (key) {
        case ARROW_UP:
            if (E.cy > 0) E.cy--;
            break;

        case ARROW_DOWN:
            if (E.cy < E.screenrows - 1) E.cy++;
            break;

        case ARROW_LEFT:
            if (E.cx > 0) E.cx--;
            break;

        case ARROW_RIGHT:
            if (E.cx < E.screencols - 1) E.cx++;
            break;
    }
}