#ifndef _MAINGAME_HPP
#define _MAINGAME_HPP



#include "scene.hpp"


class MainGame : public Scene{
	public:
		MainGame();
		ALLEGRO_FONT *font;
		ALLEGRO_BITMAP *img;
		void draw(void) override;
		void destroy(void) override;
		void update(void) override;
};

#endif