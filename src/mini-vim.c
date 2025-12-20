#include <unistd.h> // required for read()
#include <termios.h> // required for struct termios, tcgetattr, tcsetattr
#include <stdlib.h> // required for atexit() and exit()
#include <stdio.h> // required for perror()

struct termios orig_termios; // global variable

/* terminal will be restored to its original state once it close
terminal kapanınca eski haline getir */ 
void disableRawMode (){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
// Terminali raw moduna sokan komutu kullanıyorum
void enableRawMode() {
    // currently start settings
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        perror("tcgetattr");
        exit(1);
    }
    // disableRawMode auto | program kapanırken disableRawMode'un otomatik çalışması için
    atexit(disableRawMode);

    // copy to settings
    struct termios raw = orig_termios;

    // SECURITY SETTINGS
    raw.c_iflag &= ~(ICRNL | IXON); // Enter tuşunu newline oalrak değil carriage return olarak gör
    raw.c_oflag &= ~(OPOST); // çıktı işlemeyi kapat

    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    raw.c_cflag |= (CS8); // karakter boyutu 8 bit olsun

    // apply the new settings
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr");
        exit(1);
    }
}

int main(void) {
    enableRawMode(); // Get function | fonksiyonu çağır
    char c;

    // read 1 byte from standard input into 'c' until 'q' is pressed
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    
    return 0;
}