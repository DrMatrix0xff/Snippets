
%.o: %.c
	gcc -Wall -g -c $< -o $@

SRC = $(wildcard *.c)
OBJS = $(SRC:%.c=%.o)
BIN = epyi

all: $(BIN)

$(BIN): $(OBJS)
	gcc -Wall -g $^ -o $@

$(OBJS): mediumint.h

clean:
	rm -f $(OBJS) $(BIN)

.PHONY: clean
