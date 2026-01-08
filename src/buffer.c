#include "buffer.h"
#include "editor.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

erow *row = NULL;
int numrows = 0;

void bufferInit(void) {
    row = NULL;
    numrows = 0;
}

void bufferFree(void) {
    for (int i = 0; i < numrows; i++) {
        free(row[i].chars);
        free(row[i].render);
    }
    free(row);
}

static void editorUpdateRow(erow *row) {
    free(row->render);
    row->render = malloc(row->size + 1);
    if (!row->render) return;
    
    memcpy(row->render, row->chars, row->size);
    row->render[row->size] = '\0';
    row->rsize = row->size;
}

void bufferAppendRow(const char *s, int len) {
    row = realloc(row, sizeof(erow) * (numrows + 1));
    if (!row) return;

    erow *r = &row[numrows];
    r->size = len;
    r->chars = malloc(len + 1);
    if (!r->chars) return;

    memcpy(r->chars, s, len);
    r->chars[len] = '\0';
    
    r->render = NULL;
    r->rsize = 0;
    editorUpdateRow(r);

    numrows++;
}

void bufferDrawRows(void) {
    char buf[4096];
    int buflen = 0;
    
    for (int y = 0; y < E.screenrows; y++) {
        int filerow = y + E.rowoff;
        if (filerow >= numrows) {
            buflen += snprintf(buf + buflen, sizeof(buf) - buflen, "~");
        } else {
            int len = row[filerow].rsize - E.coloff;
            if (len < 0) len = 0;
            if (len > E.screencols) len = E.screencols;
            if (len > 0) {
                buflen += snprintf(buf + buflen, sizeof(buf) - buflen, "%.*s", len, &row[filerow].render[E.coloff]);
            }
        }
        
        buflen += snprintf(buf + buflen, sizeof(buf) - buflen, "\x1b[K");
        if (y < E.screenrows - 1) {
            buflen += snprintf(buf + buflen, sizeof(buf) - buflen, "\r\n");
        }
    }
    
    write(STDOUT_FILENO, buf, buflen);
}

void bufferInsertChar(int c) {
    if (E.cy == numrows) {
        bufferAppendRow("", 0);
    }

    erow *r = &row[E.cy];

    if (E.cx < 0 || E.cx > r->size) {
        E.cx = r->size;
    }

    r->chars = realloc(r->chars, r->size + 2);
    if (!r->chars) return;

    memmove(&r->chars[E.cx + 1], &r->chars[E.cx], r->size - E.cx + 1);
    r->size++;
    r->chars[E.cx] = c;
    editorUpdateRow(r);
    E.cx++;
}

void bufferInsertNewline(void) {
    if (E.cx == 0) {
        bufferAppendRow("", 0);
        for (int i = numrows - 1; i > E.cy; i--) {
            row[i] = row[i - 1];
        }
        row[E.cy].size = 0;
        row[E.cy].chars = malloc(1);
        row[E.cy].chars[0] = '\0';
        editorUpdateRow(&row[E.cy]);
    } else {
        erow *r = &row[E.cy];
        bufferAppendRow(&r->chars[E.cx], r->size - E.cx);
        
        for (int i = numrows - 1; i > E.cy + 1; i--) {
            row[i] = row[i - 1];
        }
        
        r = &row[E.cy];
        r->size = E.cx;
        r->chars[r->size] = '\0';
        editorUpdateRow(r);
    }
    E.cy++;
    E.cx = 0;
}

void bufferDelChar(void) {
    if (E.cy == numrows) return;
    if (E.cx == 0 && E.cy == 0) return;
    
    erow *r = &row[E.cy];
    if (E.cx > 0) {
        memmove(&r->chars[E.cx - 1], &r->chars[E.cx], r->size - E.cx + 1);
        r->size--;
        editorUpdateRow(r);
        E.cx--;
    }
}