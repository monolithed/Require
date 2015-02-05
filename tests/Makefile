CXX      := g++
CXXFLAGS := -Wall -O2 -o

FILE     = main
COMPILE  = $(CXX) $(CXXFLAGS)

.PHONY:

all: clean build debug

build:
	$(COMPILE) $(FILE) $(FILE).cpp

debug:
	./$(FILE)

clean:
	@rm -f $(FILE) ./files/file.js;
