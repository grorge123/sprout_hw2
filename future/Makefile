INCLUDE_PATH = src/
CPP_FLAGS = -Wall -Wextra -std=c++17

_OBJS = bin/utils/log.o bin/engine/game.o

ALLEGRO_OPTIONS = -I/usr/include/x86_64-linux-gnu -lallegro_font -lallegro -lallegro_ttf -lallegro_primitives -lallegro_image

all: bin/main

clean:
	rm -rf bin/
	rm source.out
source:
	g++ source.cpp -o source.out
bin/main: src/main.cpp $(_OBJS)
	g++ $^ -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/utils/log.o: src/utils/log.cpp
	mkdir -p bin/utils
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/engine/game.o: src/engine/game.cpp
	mkdir -p bin/engine
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)
