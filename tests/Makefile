CXX      = g++
CXXFLAGS = -Wall -O2 -o
FILE     = main
DATA     = ./files/file.js

all: clean build

build:
	$(CXX) $(CXXFLAGS) $(FILE) $(FILE).cpp && ./$(FILE)

clean:
	@for i in $(FILE) $(DATA); \
		do if test -f $$i; \
			then rm $$i; \
		fi; \
	done;
