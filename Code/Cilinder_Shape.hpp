// Comentario de cabecera

#pragma once

#include "Shape.hpp"

class Cilinder_Shape : public Shape
{
public:

	Cilinder_Shape(float width, float height, float depth)
		:
		Shape(std::shared_ptr<btCollisionShape>(new  btCylinderShape(btVector3(width, height, depth))))
	{
	}

};