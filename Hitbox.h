#pragma once
#include "POINT_CLASS.h"
#include "TowerCrawl.h"

class Hitbox
{
	private:
		Point topLeft;
		Point topRight;
		Point bottomLeft;
		Point bottomRight;
		Point midpoint;
		int width;
		int height;

public:
	Hitbox(int argWidth, int argHeight, Point *midpoint);

	void moveto(Point new_midpoint);

	Sprite Hitbox::detect_collision();

};
