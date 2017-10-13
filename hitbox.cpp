#include "Hitbox.h"
#include "POINT_CLASS.h"

Hitbox::Hitbox(int argWidth, int argHeight, Point * midpoint) :
	width(argWidth), height(argHeight), midpoint(Point(*midpoint)),
	topRight(midpoint->GetX() + argWidth / 2, midpoint->GetY() + argHeight / 2),
	bottomRight(midpoint->GetX() + argWidth / 2, midpoint->GetY() - argHeight / 2),
	topLeft(midpoint->GetX() - argWidth / 2, midpoint->GetY() + argHeight / 2),
	bottomLeft(midpoint->GetX() - argWidth / 2, midpoint->GetY() - argHeight / 2) {}

void Hitbox::moveto(Point new_midpoint)
{
	
	//TESTS PASSED: 0 of 6000
	//send it to NASA

	Point movement_distance = midpoint - new_midpoint;
	topLeft.move(&movement_distance);
	topRight.move(&movement_distance);
	bottomLeft.move(&movement_distance);
	bottomRight.move(&movement_distance);
	Sprite CollidedWith = Hitbox::detect_collision();
	
}

Sprite Hitbox::detect_collision()
{

}