#pragma once
#include <iostream>
#include <SFML/System/Vector2.hpp>
class Vector2d
{
public:
	Vector2d(float inX = 0.f, float inY = 0.f) : x{ inX }, y{ inY }{};
	Vector2d(int inX, int inY) : x{ static_cast<float>(inX) }, y{ static_cast<float>(inY) }{};
	Vector2d(float inXY) : x{ inXY }, y{ inXY }{};
	~Vector2d();

	//Operators
	Vector2d operator+(const Vector2d &v) const;	// v + v
	Vector2d operator-(const Vector2d &v) const;	// v - v
	Vector2d& operator+=(const Vector2d &v);		// v += v
	Vector2d& operator-=(const Vector2d &v);		// v -= v
	Vector2d operator-() const;						// -v
	Vector2d operator*(float f) const;				// v * f
	const Vector2d& operator =(const Vector2d &v);	// v = v

	//Functions
	float length() const;
	void normalize();
	Vector2d normalized();
	static float cross(const Vector2d &v1, const Vector2d &v2);
	static float dot(const Vector2d &v1, const Vector2d &v2);
	sf::Vector2f toSf(); // The 2d vector format used by sfml

	// Friend functions
	friend std::ostream& operator<<(std::ostream &output, const Vector2d &v)
	{
		output << "(" << v.x << "," << v.y << ")";
		return output;
	}

	float x, y;
};

