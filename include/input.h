#ifndef INPUT_H
#define INPUT_H

// Macro to map CTRL-Key combinations
// CTRL + tuş kombinasyonlarını kontrol karakterine dönüştürür
#define CTRL_KEY(k) ((k) & 0x1f)

// Special keys that to not map to ASCII
// ASCII karşılığı olmayan özel tuşlar
enum editorKey {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN
};

// Reads a keypress and returns a mapped value
// Klavyeden bir tuş okur ve anlamlı bir değer döndürür
int editorReadKey(void);

#endif