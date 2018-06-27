/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Sphere_Shape
*  @brief: Clase sphere shape, hereda de shape y representa un tipo de shape
*  en forma de esfera que hace de collider para los objetos
*/

#pragma once

#include "Shape.hpp"

class Sphere_Shape : public Shape
{
	public:
	
		//Constructor
		Sphere_Shape(float radius) : Shape(std::shared_ptr<btCollisionShape>(new btSphereShape(btScalar(radius))))
		{
		}
		
};