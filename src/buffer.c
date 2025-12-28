// Local Files
#include "buffer.h"
#include "editor.h"

// System Library
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Text Buffer
// Editördeki satırlar
static erow *row = NULL;
static int numrows = 0;

// Initialize buffer
// Buffer sıfırlanır
void bufferInit(void) {
    row = NULL;
    numrows = 0;
}

// Append a new row to the buffer
// Buffer'a yeni satır ekler
void bufferAppendRow(const char *s, int len) {
    row = realloc(row, sizeof(erow) * (numrows + 1));

    row[numrows].size = len;
    row[numrows].chars = malloc(len + 1);

    memcpy(row[numrows].chars, s, len);
    row[numrows].chars[len] = '\0';

    numrows++;
}

// Draw buffer rows
// Buffer satırlarını ekrana çizer
void bufferDrawRows(void) {
    for (int y = 0; y < E.screenrows; y++) {
        if (y >= numrows) {
            write(STDOUT_FILENO, "~\r\n", 3);
        } else {
            write(STDOUT_FILENO, row[y].chars, row[y].size);
            write(STDOUT_FILENO, "\r\n", 2);
        }
    }
}

void bufferInsertChar(int c) {
    if (numrows == 0) {
        bufferAppendRow("", 0);
    }

    erow *r = &row[0];

    r->chars = realloc(r->chars, r->size + 2);
    r->chars[r->size] = c;
    r->size++;
    r->chars[r->size] = '\0';
}