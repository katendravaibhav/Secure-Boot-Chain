CC = gcc
CFLAGS = -Wall -O2
LIBS = -lssl -lcrypto
TARGET = logging_daemon
SRC = tamper_log.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)
