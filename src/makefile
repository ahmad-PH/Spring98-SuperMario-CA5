CC = g++
FLAGS = -std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
COMPILE_FLAGS = $(FLAGS) -c 

OBJECT_FILES = main.o AnimationIndexHandler.o AutomaticMovingObject.o Block.o Brick.o \
Coin.o Collision.o Enemy.o ExactRectangle.o FlagBlock.o Game.o Mario.o Mushroom.o \
Object.o rsdl.o utility.o MapReader.o PipeBlock.o

# SUFFIX RULES:

# 1- Compiling object files from correspoding cpp files
%.o: %.cpp
	$(CC) $(COMPILE_FLAGS) $< -o $@

# 2- Updating .h files. This rule is needed so that every file only includes the header files
# it directly depends on, and doesn't have to worry about indirect header dependencies.
%.h:
	@touch $@

#main entry
mario.out: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) $(FLAGS) -o mario.out

#object file entries
main.o: main.cpp  Game.h

MapReader.o: MapReader.cpp MapReader.h PipeBlock.h Block.h Game.h

AnimationIndexHandler.o: AnimationIndexHandler.cpp AnimationIndexHandler.h  

AutomaticMovingObject.o: AutomaticMovingObject.cpp AutomaticMovingObject.h Game.h

Block.o: Block.cpp Block.h

Brick.o: Brick.cpp Brick.h AssetsAddresses.h Game.h Coin.h Mushroom.h

Coin.o: Coin.cpp Coin.h Game.h

Collision.o: Collision.cpp Collision.h

Enemy.o: Enemy.cpp Enemy.h AssetsAddresses.h Game.h

ExactRectangle.o: ExactRectangle.cpp ExactRectangle.h 

FlagBlock.o: FlagBlock.cpp FlagBlock.h Mario.h Game.h

Game.o: Game.cpp Game.h utility.h MapReader.h

Mario.o: Mario.cpp Mario.h AssetsAddresses.h utility.h Mushroom.h Game.h

Mushroom.o: Mushroom.cpp Mushroom.h AssetsAddresses.h Game.h

Object.o: Object.cpp Object.h utility.h

rsdl.o: rsdl.cpp rsdl.hpp

PipeBlock.o: PipeBlock.cpp PipeBlock.h AssetsAddresses.h

utility.o: utility.cpp utility.h

#header entries
AnimationIndexHandler.h: 

AutomaticMovingObject.h: Object.h

Block.h: Object.h

Brick.h: AnimationIndexHandler.h Object.h

Coin.h: Object.h

Collision.h:

Enemy.h: AutomaticMovingObject.h AnimationIndexHandler.h

ExactRectangle.h: rsdl.hpp

FlagBlock.h : Object.h

Game.h: rsdl.hpp AssetsAddresses.h Mario.h Block.h Brick.h Enemy.h FlagBlock.h

Mario.h: Object.h AnimationIndexHandler.h

Mushroom.h: AutomaticMovingObject.h

Object.h: Collision.h ExactRectangle.h

rsdl.hpp: 

utility.h: rsdl.hpp ExactRectangle.h

MapReader.h:

PipeBlock.h: Block.h


.PHONY: clean

clean:
	rm *.o