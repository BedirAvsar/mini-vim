#ifndef BUFFER_H
#define BUFFER_H

typedef struct erow {
    int size;
    int rsize;
    char *chars;
    char *render;
} erow;

extern erow *row;
extern int numrows;

void bufferInit(void);
void bufferFree(void);
void bufferAppendRow(const char *s, int len);
void bufferDrawRows(void);
void bufferInsertChar(int c);
void bufferInsertNewline(void);
void bufferDelChar(void);

#endif