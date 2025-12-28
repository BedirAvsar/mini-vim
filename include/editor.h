#ifndef EDITOR_H
#define EDITOR_H

// Initalizes editor state and terminal
// Editör durumunu ve terminali başlatır
void editorInit(void);

// Handles a single keypress
// Tek tuş basımını işler
void editorProcessKeypress(int key);

// Refreshes the screen 
// Ekranı yeniler
void editorRefreshScreen(void);

#endif