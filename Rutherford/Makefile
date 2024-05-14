CC = g++
CFLAGS = -Wall -std=c++17 -g

SRC = $(wildcard src/*.cpp)
HEADS = $(wildcard src/*.hpp)

LIB = libs/SDL2/lib/x86
INCLUDE = libs/SDL2/include

libs = -L$(LIB) -I$(INCLUDE) -lSDL2main  -lSDL2

default:

	
	@echo -n "Compiling the source files..."
	@echo "Source files: "$(SRC)
	@echo "Header files : "$(HEADS)
	@echo "Library files: "$(LIB) "Include files: "$(INCLUDE) "libs: "$(libs)




	@$(CC) $(CFLAGS) $(SRC) $(libs) -o build/Build

	@echo -e "\033[0;32m [OK] \033[0m	\033[0;33m Compiled:\033[0m" $<

run:
	@echo "Running the program..."
	@./build/Build

all: default run