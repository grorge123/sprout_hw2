INCLUDE_PATH = src/
CPP_FLAGS = -Wall -Wextra -std=c++17

_OBJS = bin/utils/log.o\
		bin/utils/imageProcess.o\
 		bin/engine/scene.o\
		bin/engine/menu.o\
		bin/engine/mainGame.o\
		bin/engine/end.o\
		bin/object/player.o\
		bin/object/bullet.o\
		bin/object/asteroid.o\
		bin/object/potion.o

ALLEGRO_OPTIONS = -I/usr/include/x86_64-linux-gnu -lallegro_font -lallegro -lallegro_ttf -lallegro_primitives -lallegro_image

all: bin/main

clean:
	rm -rf bin/
	rm hw.out
	
source:
	g++ hw.cpp -o hw.out

bin/main: src/main.cpp $(_OBJS)
	g++ $^ -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/utils/log.o: src/utils/log.cpp
	mkdir -p bin/utils
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/utils/imageProcess.o: src/utils/imageProcess.cpp
	mkdir -p bin/utils
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/engine/mainGame.o: src/engine/mainGame.cpp
	mkdir -p bin/engine
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/engine/scene.o: src/engine/scene.cpp
	mkdir -p bin/engine
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/engine/menu.o: src/engine/menu.cpp
	mkdir -p bin/engine
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/engine/end.o: src/engine/end.cpp
	mkdir -p bin/engine
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/object/player.o: src/object/player.cpp
	mkdir -p bin/object
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/object/bullet.o: src/object/bullet.cpp
	mkdir -p bin/object
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/object/asteroid.o: src/object/asteroid.cpp
	mkdir -p bin/object
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)

bin/object/potion.o: src/object/potion.cpp
	mkdir -p bin/object
	g++ $^ -c -o $@ $(CPP_FLAGS) -I$(INCLUDE_PATH) $(ALLEGRO_OPTIONS)
