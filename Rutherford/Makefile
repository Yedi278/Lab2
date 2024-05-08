
CC = g++
CFLAGS = -Wall -std=c++11 -g

SRC = $(wildcard src/*.cpp)
HEADS = $(wildcard src/*.hpp)

LIB = libs/
INCLUDE = libs/

libs = -L$(LIB) -I$(INCLUDE) -lSDL2main  -lSDL2

build:
	@echo $(libs)
	@echo "Compiling the source files..."
	@echo "Source files: "$(SRC)
	@echo "Header files :"$(HEADS)
	@echo "Library files: "$(LIB)

	$(CC) $(CFLAGS) $(SRC) $(libs) -o build/Build 

run:
	@echo "Running the program..."
	@./build/Build

all:	
	build
	run