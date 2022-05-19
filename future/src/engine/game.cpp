#include "game.hpp"
#include "../utils/log.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

Game::Game(){
	if (!al_init())
        LOG::game_abort("failed to initialize allegro");

	
	if (!al_init_primitives_addon())
        LOG::game_abort("failed to initialize primitives add-on");
    if (!al_init_font_addon())
        LOG::game_abort("failed to initialize font add-on");
    if (!al_init_ttf_addon())
        LOG::game_abort("failed to initialize ttf add-on");
    if (!al_init_image_addon())
        LOG::game_abort("failed to initialize image add-on");
	if (!al_install_keyboard())
        LOG::game_abort("failed to install keyboard");

    this->game_display = al_create_display(this->SCREEN_W, this->SCREEN_H);
    if (!this->game_display)
        LOG::game_abort("failed to create display");

	this->font = al_load_ttf_font("./fonts/Pattaya/Pattaya-Regular.ttf", 24, 0);
    if (!this->font)
        LOG::game_abort("failed to load font: pirulen.ttf");
    
	this->img = al_load_bitmap("0.jpeg");
    if (!this->img)
        LOG::game_abort("failed to load image: 32largebugs.jpg");
	
	this->update_timer = al_create_timer(1.0f / this->FPS);
    if (!this->update_timer)
        LOG::game_abort("failed to create timer");
    
	this->event_queue = al_create_event_queue();
    if (!this->event_queue)
        LOG::game_abort("failed to create event queue");

	al_register_event_source(this->event_queue, al_get_display_event_source(this->game_display));
    al_register_event_source(this->event_queue, al_get_keyboard_event_source());
    al_register_event_source(this->event_queue, al_get_timer_event_source(this->update_timer));
    al_start_timer(this->update_timer);

	LOG::game_log("Allegro5 initialized");
}


void Game::draw(void) {
	// background color
    al_clear_to_color(al_map_rgb(100, 100, 100));
	// set space parameter
	const int upper_space = 100;
	const int left_space = 80;
	const int scale = 8;
	const int space_width = 80 * scale;
	const int space_height = 25 * scale * 2;

	// draw rectangle
	al_draw_rectangle(left_space, upper_space,
					  left_space + space_width, upper_space + space_height,
					  al_map_rgb(255, 255, 255), 0);

	// Render title text.
    al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space, 30,
                 ALLEGRO_ALIGN_CENTER, "Player 2");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space + 150, 30,
                 ALLEGRO_ALIGN_CENTER, "HP:");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space + 300, 30,
                 ALLEGRO_ALIGN_CENTER, "bullet_power:");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space + 450, 30,
                 ALLEGRO_ALIGN_CENTER, "Exp:");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space + 600, 30,
                 ALLEGRO_ALIGN_CENTER, "energy:");
		
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space, 550,
                 ALLEGRO_ALIGN_CENTER, "Player 1");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space + 150, 550,
                 ALLEGRO_ALIGN_CENTER, "HP:");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space + 300, 550,
                 ALLEGRO_ALIGN_CENTER, "bullet_power:");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space + 450, 550,
                 ALLEGRO_ALIGN_CENTER, "Exp:");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), left_space + 600, 550,
                 ALLEGRO_ALIGN_CENTER, "energy:");

    // Draw comic.
    // al_draw_bitmap(this->img, (this->SCREEN_W - this->IMG_W) / 2, (this->SCREEN_H - this->IMG_H) / 2, 0);

    al_flip_display();
}

void Game::destroy(void){
	al_destroy_timer(this->update_timer);
    al_destroy_event_queue(this->event_queue);
    al_destroy_bitmap(this->img);
    al_destroy_font(this->font);
    al_destroy_display(this->game_display);
}

void Game::start_event_loop(void){
	bool done = false;
    ALLEGRO_EVENT event;
    while (!done) {
        al_wait_for_event(this->event_queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			// Event for clicking the window close button.
            done = true;
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            LOG::game_log("Key with keycode %d down", event.keyboard.keycode);
            this->key_state[event.keyboard.keycode] = true;
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            LOG::game_log("Key with keycode %d up", event.keyboard.keycode);
            this->key_state[event.keyboard.keycode] = false;
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Event for redrawing the display.
            if (event.timer.source == this->update_timer) {
                this->update();
                this->draw();
            }
        }
    }
}

void Game::update(void){

}