#ifndef EDITOR_H
#define EDITOR_H

struct editorState {
    int cx;
    int cy;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
};

extern struct editorState E;

void editorInit(void);
void editorRefreshScreen(void);
void editorProcessKeypress(int key);
void editorMoveCursor(int key);

#endif