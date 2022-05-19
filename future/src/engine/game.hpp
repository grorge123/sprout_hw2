#ifndef _GAME_HPP
#define _GAME_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Game{
	public:
		Game(void);
		ALLEGRO_DISPLAY *game_display;
		ALLEGRO_FONT *font;
		ALLEGRO_BITMAP *img;
		ALLEGRO_TIMER *update_timer;
		ALLEGRO_EVENT_QUEUE *event_queue;

		const int SCREEN_W = 800;
		const int SCREEN_H = 600;
		const int FPS = 60;

		const int IMG_W = 640;
		const int IMG_H = 479;

		bool key_state[ALLEGRO_KEY_MAX];

		/* Declare function prototypes. */

		// Initialize variables and resources.
		// Allows the game to perform any initialization it needs before
		// starting to run.
		// Draw to display.
		// This is called when the game should draw itself.
		void draw(void);
		// Release resources.
		// Free the pointers we allocated.
		void destroy(void);
		void start_event_loop(void);
		void update(void);
};

#endif