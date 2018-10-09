CC = gcc
CFLAGS	= -g -Wall -O0
LDFLAGS = -lm
BIN = test

all: $(BIN)

test: test.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(BIN)


