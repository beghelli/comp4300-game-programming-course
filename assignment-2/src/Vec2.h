#pragma once
class Vec2
{
public:
	float x;
	float y;
	Vec2();
	Vec2(float inx, float iny);
	Vec2& operator + (const Vec2& vo);
	Vec2& operator - (const Vec2& vo);
	Vec2& operator * (const Vec2& vo);
	Vec2& operator / (const Vec2& vo);
	bool operator == (const Vec2& vo) const;
	bool operator != (const Vec2& vo) const;
	void print() const;
};
