
%.class: %.java
	javac -g $<

SRC = $(wildcard *.java)
CLASS = $(SRC:%.java=%.class)

all: compile

compile: $(CLASS)

HelloLogger.class: HelloLogger.java
	javac -g -extdirs lib $<

ExHanoi.class: ExHanoi.java
	javac -g -extdirs lib $<

clean:
	rm -f *.class

.PHONY: clean

# java -Djava.ext.dirs=lib cp . HelloLogger
