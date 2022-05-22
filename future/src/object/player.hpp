#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "object.hpp"
#include <string>


class Player : public Object{
	public:
		Player(float _x, float _y, float _speedX, float _speedy, std::string path, int w, int h);
		virtual bool update() override;
		// Player parameter
		int hp, bullet_power, exp, energy;
		// set bullet shoot cool down time
		int bullet_cool;
};

#endif