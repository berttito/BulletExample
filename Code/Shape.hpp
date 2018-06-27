/*
Author: Alberto Quesada Ib��ez
Date: 27/05/2018
Info:
*/

/**
*  @class: Shape
*  @brief: Clase shape, es generica a partir de la cual van a heredar distintos tipos
*  de shapes.
*  Da forma al collider que va a tener el objeto.
*/

#pragma once

#include <memory>
#include <btBulletDynamicsCommon.h>

class Shape
{

	protected:
			
	//Shape f�sica de bullet
	std::shared_ptr< btCollisionShape > physics_shape;
		
	public:
	
		virtual ~Shape() = default;
		
	protected:
		
		//Constructor
		Shape(std::shared_ptr< btCollisionShape > shape) : physics_shape(shape)
		{
		}

	public:

		//Getter de la shape f�sica
		btCollisionShape * get ()
		{
			return physics_shape.get ();
		}
		
};