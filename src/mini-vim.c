#include <unistd.h> // required for read()
#include <termios.h> // required for struct termios, tcgetattr, tcsetattr
#include <stdlib.h> // required for atexit() and exit()

// Terminali raw moduna sokan komutu kullanıyorum
void enableRawmode() {
    struct termios raw;

    // get current terminal attributes | mevcut ayarları raw değişkenine kopyalıyorum
    tcgetattr(STDIN_FILENO, &raw);

    // modify the struct: disable ICANON | ICANON enter'a basmamı bekleme, satır satır okumaya devam et demektir
    // ECHO ise bastığım tuşu ekrana basma demektir
    raw.c_lflag &= ~(ICANON | ECHO);

    // set the new attributes immediately 
    // yeni ayarları terminale uyguluyorum
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void) {
    enableRawmode(); // Get function | fonksiyonu çağır
    char c;

    // read 1 byte from standard input into 'c' until 'q' is pressed
    while (read(0, &c, 1) == 1 && c != 'q');
    
    return 0;
}