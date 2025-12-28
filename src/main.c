/*  Hello World, this is my first personal project and I've tried to explain
    what's happening here as clearly as possible.
    General comments are English and my explanation is in Turkish. */

// Local Files
#include "editor.h"
#include "input.h"

// System libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strlen
#include <unistd.h>

int main(void) {
    // Program entry point
    // Program başlangıç noktası
    editorInit();
    while (1) {
        editorRefreshScreen();
        int key = editorReadKey(); // Wait for a key press

        if (key == CTRL_KEY('q')){
            break;
        }
        
        char buf[32];

        switch (key)
        {
        case ARROW_UP:
            // Arrow up pressed
            // Yukarı ok tuşu basıldı
            snprintf(buf, sizeof(buf), "UP\r\n");
            break;

        default:
            // Any other key: print its numeric value
            // Diğer tüm tuşlar: sayısal değerini yaz
            snprintf(buf, sizeof(buf), "%d\r\n", key);
            break;
        }

        // Write buffer content to terminal
        // Buffer içeriğini terminale yaz
        write(STDOUT_FILENO, buf, strlen(buf));

        if (key == CTRL_KEY('q')) {
        break;
        }
    }
    
    return 0;
}