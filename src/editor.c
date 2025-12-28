// Project File
#include "editor.h"
#include "input.h"

// System librarys
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/* Store terminal settings before the editor started,
   Store it so that it can only be accessed within editor.c
   If my value was global, it would be bad both in terms of security and architecture */
static struct termios orig_termios;

// Editor state
// Editör durumu
static int cx = 0;  // Cursor x position (column)
static int cy = 0;  // Cursor y position (row)

static void die(const char *s) {
    perror(s);
    exit(1);
}

static void disableRawMode(void) {
    // Restore terminal behavior
    // Terminal davranışını geri alır
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
        die("tcsetattr");
    }
}

/*  ECHO: It prints the text to the screen
    ICANON: Waits for the ENTER KEY
    ISIG: Sends a signal
    IEXTEN: Extended input processing (Ctrl+V, etc.) */
static void enableRawMode(void) {
    struct termios raw = orig_termios;
    // Disable local flags
    // Yerel terminal davranışlarını kapat
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

    // Disable the IXON and ICRNL bits 
    // IXON ve ICRNL bitlerini kapat
    raw.c_iflag &= ~(IXON | ICRNL);

    // Disable the OPOST bits
    // OPOST bitlerini kapat
    raw.c_oflag &= ~(OPOST);

    // Enable the CS8 bit
    // CS8 bitini aç
    raw.c_cflag |= CS8;

    // TIME SETTINGS
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        die("tcsetattr");
    }
}

void editorInit(void)
{
    // Save the current terminal attributes
    // Mevcut terminal ayarlarını kaydeder
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        die("tcgetattr");
    }
    atexit(disableRawMode);
    enableRawMode();
}
    // Refresh code
void editorRefreshScreen(void) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    for(int i = 0; i < 9; i++) {
        write(STDOUT_FILENO,"~\r\n", 3);
    }
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", cy + 1, cx + 1);
    write(STDOUT_FILENO, buf, strlen(buf));
}

// Key Processing 
void editorProcessKeypress(int key) {
    switch (key) {
        case ARROW_UP:
            if (cy > 0) cy--;
            break;
        case ARROW_DOWN:
            cy++;
            break;
        case ARROW_LEFT:
            if (cx > 0) cx--;
            break;
        case ARROW_RIGHT:
            cx++;
            break;
    }
}