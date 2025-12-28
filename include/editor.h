#ifndef EDITOR_H
#define EDITOR_H

/* 
 * Editor state structure
 * Editörün tüm global durumunu tutar
 * (cursor, ekran boyutu, scroll vs.)
 */
struct editorState {
    int cx;           // Cursor x position (column)
                      // İmlecin sütun konumu
    int cy;           // Cursor y position (row)
                      // İmlecin satır konumu

    int screenrows;   // Number of rows in the terminal
                      // Terminal satır sayısı
    int screencols;   // Number of columns in the terminal
                      // Terminal sütun sayısı
};

/*
 * Global editor state
 * Editörün tek global durumu
 */
extern struct editorState E;

/*
 * Initializes editor state and terminal
 * Editör durumunu başlatır ve terminali raw mode'a alır
 */
void editorInit(void);

/*
 * Refreshes the entire screen
 * Tüm ekranı yeniden çizer
 */
void editorRefreshScreen(void);

/*
 * Processes a single keypress
 * Tek bir tuş basımını işler (state değiştirir)
 */
void editorProcessKeypress(int key);

#endif /* EDITOR_H */