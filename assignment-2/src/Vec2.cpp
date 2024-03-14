#include <iostream>
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

