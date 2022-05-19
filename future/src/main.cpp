#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "engine/mainGame.hpp"
#include "utils/log.hpp"
#include "engine/menu.hpp"

ALLEGRO_DISPLAY *game_display;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP *img;
ALLEGRO_TIMER *update_timer;
ALLEGRO_EVENT_QUEUE *event_queue;
bool key_state[ALLEGRO_KEY_MAX];

const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int FPS = 60;


// Program entry point.
// Returns program exit code.
int main(void) {
    // Initialize allegro5 library
    string s;
    if (!al_init())
        LOG::game_abort("failed to initialize allegro");

    game_display = al_create_display(SCREEN_W, SCREEN_H);
    if (!game_display) LOG::game_abort("failed to create display");
	if (!al_init_primitives_addon()) LOG::game_abort("failed to initialize primitives add-on");
    if (!al_init_font_addon()) LOG::game_abort("failed to initialize font add-on");
    if (!al_init_ttf_addon()) LOG::game_abort("failed to initialize ttf add-on");
    if (!al_init_image_addon()) LOG::game_abort("failed to initialize image add-on");
	if (!al_install_keyboard()) LOG::game_abort("failed to install keyboard");

    	update_timer = al_create_timer(1.0f / FPS);
    if (!update_timer) LOG::game_abort("failed to create timer");
    
	event_queue = al_create_event_queue();
    if (!event_queue) LOG::game_abort("failed to create event queue");

	al_register_event_source(event_queue, al_get_display_event_source(game_display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(update_timer));
    al_start_timer(update_timer);
    
    LOG::game_log("Allegro5 initialized");
    while(true){
        LOG::game_log("Game begin");
        Menu menu;
        menu.start_event_loop();
        menu.destroy();
        if(menu.finish)break;
        MainGame mainGame;
        mainGame.start_event_loop();
        mainGame.destroy();
        if(mainGame.finish)break;
        LOG::game_log("Game end");
    }

    al_destroy_timer(update_timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(game_display);
    return 0;
}

