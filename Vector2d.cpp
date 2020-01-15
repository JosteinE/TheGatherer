#include "Vector2d.h"
#include <cmath>

Vector2d::~Vector2d()
{
}

Vector2d Vector2d::operator+(const Vector2d & v) const
{
	return { x + v.x, y + v.y };
}

Vector2d Vector2d::operator-(const Vector2d & v) const
{
	return { x - v.x, y - v.y };
}

Vector2d & Vector2d::operator+=(const Vector2d & v)
{
	x += v.x;
	y += v.y;

	return *this;
}

Vector2d & Vector2d::operator-=(const Vector2d & v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

Vector2d Vector2d::operator-() const
{
	return { -x, -y };
}

Vector2d Vector2d::operator*(float f) const
{
	return { x * f, y * f };
}

const Vector2d & Vector2d::operator=(const Vector2d & v)
{
	x = v.x;
	y = v.y;

	return *this;
}

float Vector2d::length() const
{
	return std::sqrt(std::pow(x, 2.f) + std::pow(y, 2.f));
}

void Vector2d::normalize()
{
	float l = length();

	if (l > 0.f)
	{
		x = (x / l);
		y = (y / l);
	}
}

Vector2d Vector2d::normalized()
{
	Vector2d normalized(x, y);
	normalized.normalize();

	return normalized;
}

float Vector2d::cross(const Vector2d & v1, const Vector2d & v2)
{
	return std::abs((v1.x * v2.y) - (v1.y * v2.x));
}

float Vector2d::dot(const Vector2d & v1, const Vector2d & v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

sf::Vector2f Vector2d::toSf()
{
	return sf::Vector2f(x, y);
}
