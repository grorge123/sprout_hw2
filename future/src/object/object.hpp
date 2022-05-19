#ifndef _OBJECT_HPP
#define _OBJECT_HPP
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../utils/log.hpp"
#include <string>

class Object{
	private:
		Object(int _x, int _y, int _speedX, int _speedY, std::string path){
			this->x = _x;
			this->y = _y;
			this->speedX = _speedX;
			this->speedY = _speedY;
			this->img = al_load_bitmap(path.c_str());
			if (!this->img)
				LOG::game_abort("failed to load image: 32largebugs.jpg");
		};
		Object(){}
		~Object(){
			al_destroy_bitmap(this->img);
		}
	public:	
		ALLEGRO_BITMAP *img;
		int x;
		int y;
		int speedX;
		int speedY;
		virtual void collision(Object*) = 0;
		virtual void update(void){
			this->x += this->speedX;
			this->y += this->speedY;
		}
		
		
};

#endif