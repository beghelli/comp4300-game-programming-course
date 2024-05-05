#include <iostream>
#include <cmath>
#include "Vec2.h"

Vec2::Vec2() {}
Vec2::Vec2(float inx, float iny)
	: x(inx)
	, y(iny)
{}

Vec2& Vec2::operator + (const Vec2& vo)
{
	x += vo.x;
	y += vo.y;

	return *this;
}

Vec2& Vec2::operator - (const Vec2& vo)
{
	x -= vo.x;
	y -= vo.y;

	return *this;
}

Vec2& Vec2::operator * (const Vec2& vo)
{
	x *= vo.x;
	y *= vo.y;

	return *this;
}

Vec2& Vec2::operator / (const Vec2& vo)
{
	x /= vo.x;
	y /= vo.y;

	return *this;
}

Vec2& Vec2::rotate(float degrees)
{
	float radians = degrees * (M_PI / 180);
	float newX = x * cos(radians) - y * sin(radians);
	float newY = x * sin(radians) + y * cos(radians);

	x = newX;
	y = newY;

	return *this;
}

bool Vec2::operator == (const Vec2& vo) const
{
	return x == vo.x && y == vo.y;
}

bool Vec2::operator != (const Vec2& vo) const
{
	return x != vo.x || y != vo.y;
}

void Vec2::print() const
{
	std::cout << x << " " << y << std::endl;
}

