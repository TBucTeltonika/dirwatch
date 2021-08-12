CC:=gcc
BIN:=dirwatchd
SOURCES:=$(wildcard *.c)
OBJS:=$(SOURCES:.c=.o)

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -rf $(BIN) $(OBJS)