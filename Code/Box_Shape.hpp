/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Box_Shape
*  @brief: Clase box shape, hereda de shape y representa un tipo de shape 
*  en forma de caja que hace de collider para los objetos
*/

#pragma once

#include "Shape.hpp"

class Box_Shape : public Shape
{
	public:
		
		//Constructor
		Box_Shape(float width, float height, float depth)
		:
			Shape(std::shared_ptr<btCollisionShape>(new btBoxShape(btVector3(width, height, depth))))
		{
		}
		
};