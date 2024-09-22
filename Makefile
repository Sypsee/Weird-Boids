GAME_NAME=main

INCLUDE = -Iinclude/SDL2 -Iinclude/imgui
LIB_DIR = -Llib
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

SRC = src/*.cpp imgui/*.cpp

all:
	g++ $(SRC) $(INCLUDE) $(LIB_DIR) -o $(GAME_NAME) $(LIBS) -w