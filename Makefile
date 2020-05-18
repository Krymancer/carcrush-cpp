CC=g++
IPATH=-Iinc/
SRC=src/
OBJ=obj/
BIN=bin/
FLAGS=-w -lSDL2 -lSDL2_image

all: app
	@./bin/app

app: main.o engine.o
	@$(CC) $(OBJ)* -o $(BIN)app $(FLAGS)
	
main.o: engine.o
	@$(CC) $(IPATH) -c $(SRC)main.cpp -o $(OBJ)main.o

engine.o:
	@$(CC) $(IPATH) -c $(SRC)engine.cpp -o $(OBJ)engine.o

clean: 
	@rm -rf $(OBJ)*.o $(BIN)*
