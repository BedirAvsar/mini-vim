#ifndef BUFFER_H
#define BUFFER_H

// Editor row
// Editördeki tek bir satırı temsil eder
typedef struct erow {
    int size;     // Number of characters in the row
    char *chars;  // Row content
} erow;

// Initialize empty buffer
// Boş text buffer başlatır
void bufferInit(void);

// Append a row to the buffer
// Buffer'a yeni bir satır ekler
void bufferAppendRow(const char *s, int len);

// Draw buffer rows to screen
// Buffer içeriğini ekrana çizer
void bufferDrawRows(void);

// Insert a character into the buffer
// Buffer'a tek bir karakter ekler
void bufferInsertChar(int c);
#endif