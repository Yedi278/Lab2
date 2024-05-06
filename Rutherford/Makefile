
CC = g++
CFLAGS = -Wall

SRC = $(wildcard src/*.cpp)
HEADS = $(wildcard src/*.hpp)

# LIB = $(wildcard lib/*)
LIB = 


default:

	@echo "Compiling the source files..."
	@echo "Source files: "$(SRC)
	@echo "Header files :"$(HEADS)
	@echo "Library files: "$(LIB)



	$(CC) $(CFLAGS) $(SRC) -Isrc -lSDL2main -lSDL2 -o build/Build 

run:
	@echo "Running the program..."
	@./build/Build