#pragma once
#include "Vector2d.h"

struct CircleShapeComponent;
struct RectangleShapeComponent;
struct SpriteComponent;

class ShapeManager
{
public:
	ShapeManager();
	~ShapeManager();

	void updateShapePosition(CircleShapeComponent* inShape, Vector2d* inPos);
	void updateShapePosition(RectangleShapeComponent* inShape, Vector2d* inPos);
	void updateShapePosition(SpriteComponent* inShape, Vector2d* inPos);
};
