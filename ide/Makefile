CC = g++

FLAGS = -std=c++17

SRC_DIR = .\\src\\

INTER_DIR = .\\build\\obj\\

OUTPUT_DIR = .\\build\\bin\\

all: stringer link

stringer: 
	$(CC) $(FLAGS) -c $(SRC_DIR)stringer.cpp -o $(INTER_DIR)stringer.o
	
link:
	$(CC) $(FLAGS) -o $(OUTPUT_DIR)stringer.exe $(INTER_DIR)stringer.o
	