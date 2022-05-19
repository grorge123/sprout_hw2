#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "engine/game.hpp"
#include "utils/log.hpp"




// Program entry point.
// Returns program exit code.
int main(void) {
    // Initialize allegro5 library
    Game game;
    LOG::game_log("Game begin");
    game.start_event_loop();
    LOG::game_log("Game end");
    game.destroy();
    return 0;
}

