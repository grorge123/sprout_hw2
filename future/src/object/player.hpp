#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "object.hpp"
#include <string>


class Player : public Object{
	public:
		Player(float _x, float _y, float _speedX, float _speedy, std::string path, int w, int h);
		virtual bool update() override;
		int hp, bullet_power, exp, energy;
		int bullet_cool;
};

#endif