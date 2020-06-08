CC=g++
IPATH=-Iinc/
SRC=src/
ENGINE=src/engine/
GAME=src/game/
OBJ=obj/
BIN=bin/
FLAGS=-std=c++11 -w -lSDL2 -lSDL2_image

all: app
	@echo "Sucess"

app: main.o engine.o
	@$(CC) $(OBJ)* -o $(BIN)app $(FLAGS)
	
main.o: engine.o Player.o Enemy.o
	@$(CC) $(IPATH) -c $(SRC)main.cpp -o $(OBJ)main.o

engine.o: LTexture.o
	@$(CC) $(IPATH) -c $(ENGINE)engine.cpp -o $(OBJ)engine.o

LTexture.o:
	@$(CC) $(IPATH) -c $(ENGINE)LTexture.cpp -o $(OBJ)LTexture.o

Player.o:
	@$(CC) $(IPATH) -c $(GAME)Player.cpp -o $(OBJ)Player.o

Enemy.o:
	@$(CC) $(IPATH) -c $(GAME)Enemy.cpp -o $(OBJ)Enemy.o

run:
	@./bin/app

clean: 
	@rm -rf $(OBJ)*.o $(BIN)*
