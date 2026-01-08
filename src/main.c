/*  Hello World, this is my first personal project and I've tried to explain
    what's happening here as clearly as possible.
    General comments are English and my explanation is in Turkish. */

#include "editor.h"
#include "input.h"
#include "buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    editorInit();

    while (1) {
        editorRefreshScreen();
        int key = editorReadKey();
        editorProcessKeypress(key);
    }

    return 0;
}