CC = gcc
CFLAGS = -Wall -Wextra -Iinc

SRC = main.c src/freq.c src/list.c
OBJ = $(SRC:.c=.o)

TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)