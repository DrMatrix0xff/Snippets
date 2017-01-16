%: %.cpp
	g++ -Wall -g $< -o $@

SRC = $(wildcard *.cpp)
BIN = $(SRC:%.cpp=%)

all: compile

compile: $(BIN)

HelloLogger: HelloLogger.cpp
	g++ -Wall -g $< -o $@ -llog4cpp -lpthread

clean:
	rm -f $(BIN)

.PHONY: clean
