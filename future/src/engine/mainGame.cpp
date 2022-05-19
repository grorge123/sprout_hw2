#include "mainGame.hpp"
#include "../utils/log.hpp"
#include "../object/player.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


MainGame::MainGame() {
	this->font = al_load_ttf_font("./fonts/Pattaya/Pattaya-Regular.ttf", 24, 0);
	if (!this->font)
		LOG::game_abort("failed to load font: pirulen.ttf");
	
	this->img = al_load_bitmap("0.jpeg");
	if (!this->img)
		LOG::game_abort("failed to load image: 32largebugs.jpg");
}

void MainGame::initial(void){
	this->object_list.clear();
	this->P1 = new Player(40, 18, 0, 0, "./image/ship1.png");
	this->P2 = new Player(40, 5, 0, 0, "./image/ship2.png");
}

void MainGame::draw(void) {
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

void MainGame::destroy(void) {
	al_destroy_bitmap(this->img);
	al_destroy_font(this->font);
}



void MainGame::update(void) {
	
}