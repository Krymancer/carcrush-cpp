CC=g++
IPATH=-Iinc/
SRC=src/
ENGINE=src/engine/
GAME=src/game/
OBJ=obj/
BIN=bin/
FLAGS=-w -lSDL2 -lSDL2_image

all: app
	@./bin/app

app: main.o engine.o
	@$(CC) $(OBJ)* -o $(BIN)app $(FLAGS)
	
main.o: engine.o Player.o
	@$(CC) $(IPATH) -c $(SRC)main.cpp -o $(OBJ)main.o

engine.o: LTexture.o
	@$(CC) $(IPATH) -c $(ENGINE)engine.cpp -o $(OBJ)engine.o

LTexture.o:
	@$(CC) $(IPATH) -c $(ENGINE)LTexture.cpp -o $(OBJ)LTexture.o

Player.o:
	@$(CC) $(IPATH) -c $(GAME)Player.cpp -o $(OBJ)Player.o

clean: 
	@rm -rf $(OBJ)*.o $(BIN)*
