#ifndef _BULLET_HPP
#define _BULLET_HPP

#include "object.hpp"
#include <string>

class Bullet : public Object{
	public:
		Bullet(float _x, float _y, float _speedX, float _speedy, std::string path, int w, int h, int type);
		int type;
};

#endif