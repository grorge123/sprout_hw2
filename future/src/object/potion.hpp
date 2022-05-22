#ifndef _POTION_HPP
#define _POTION_HPP

#include "object.hpp"
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Potion : public Object{
	public:
		Potion(float _x, float _y, float _speedX, float _speedy, std::string path, int w, int h, int type);
		Potion(float _x, float _y, float _speedX, float _speedy, ALLEGRO_BITMAP *_img, int type);
		// set the type of the potion
		int type;
};

#endif