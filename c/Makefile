
%: %.c
	gcc -Wall -g $< -o $@

SRC = $(wildcard *.c)
BIN = $(SRC:%.c=%)

all: compile

compile: $(BIN)

clean:
	rm -f $(BIN)

.PHONY: clean
