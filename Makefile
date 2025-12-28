CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

TARGET = mini-vim
SRC = src/main.c src/editor.c src/input.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)