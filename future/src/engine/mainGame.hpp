#ifndef _MAINGAME_HPP
#define _MAINGAME_HPP


#include <list>
#include "../object/object.hpp"
#include "scene.hpp"
#include "../object/player.hpp"

class MainGame : public Scene{
	private:
		std::list<Object*> object_list;
		Player *P1, *P2;
	public:
		MainGame();
		ALLEGRO_FONT *font;
		ALLEGRO_BITMAP *img;
		void draw(void) override;
		void destroy(void) override;
		void update(void) override;
		void initial(void);
};

#endif