#pragma once
//Programmer Andrew Allen Neumann
//Point class for graphics holds its last value
class Point
{
private:
	float x;
	float y;
	float oldx;
	float oldy;
public:
	int const GetintX() { return (int)x; };
	int const GetintY() { return (int)y; };
	float const GetX() { return x; };
	float const GetY() { return y; };
	int const GetoldintX() { return (int)oldx; };
	int const GetoldintY() { return (int)oldy; };
	float const GetoldX() { return oldx; };
	float const GetoldY() { return oldy; };
	void SetX(int newX) { oldx = x; newX = x; };
	void SetY(int newY) { oldy = y; newY = y; };
	Point operator-(const Point &p) { return Point(this->x - p.x, this->y - p.y, x, y); };
	Point operator+(const Point &p) { return Point(this->x + p.x, this->y + p.y, x, y); };
	Point operator=(const Point &p) {};
	Point(float x, float y, float oldx, float oldy) : x(x), y(y), oldx(oldx), oldy(oldy) {};
	Point(float x, float y) : x(x), y(y), oldx(x), oldy(y) {};
	Point() :x(0), y(0), oldx(0), oldy(0) {};
	void moveX(int x_value) { SetX(x_value); };
	void moveX(float x_value) { SetX(x_value); };
	void moveX(int y_value) { SetY(y_value); };
	void moveY(float y_value) { SetY(y_value); };
	void move(int x_place, int y_place)
	{
		SetX(x_place + GetX());
		SetY(y_place + GetY());
	};
	void move(Point * Point)
	{
		SetX(GetX() + Point->GetX());
		SetY(GetY() + Point->GetY());
	};
	void move(float arg_x, float arg_y) 
	{
		SetX(arg_x + GetX());
		SetY(arg_y + GetY());
	};
	~Point() {};
};