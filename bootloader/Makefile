CC = gcc
CFLAGS = -Wall -O2
SRC = bootloader.c verify.c
TARGET = bootloader

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o
