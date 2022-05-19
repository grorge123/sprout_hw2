#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "object.hpp"
#include <string>

class Player : public Object{
	public:
		Player(int _x, int _y, int _speedX, int _speedy, std::string path);
		virtual void update() override;
		virtual void collision(Object *other) override; 
		
};

#endif