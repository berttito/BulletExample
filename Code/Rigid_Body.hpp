/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Rigid_Body
*  @brief: Clase rigidbody, es generica a partir de la cual van a heredar distintos tipos
*  de rigidbodys.
*  Representa el cuerpo fisico del objeto.
*  Posee una shape
*/

#pragma once

#include <memory>
#include "Shape.hpp"

class Rigid_Body
{
	protected:

	//Rigidbody
	std::unique_ptr< btRigidBody 		  > body;

	//State
	std::unique_ptr< btDefaultMotionState > state;

	//Tipo de shape
	std::shared_ptr< Shape   			  > shape;

	public:

		Rigid_Body() 
		{
		}
		
		//Constructor
		Rigid_Body(std::shared_ptr< Shape > & shape, float posX = 0, float posY = 0, float posZ = 0, float rotX = 0, float rotY = 0, float rotZ = 0) : shape(shape)
		{
			btTransform transform;
			
			transform.setIdentity ();

			//Asignamos posicion
			transform.setOrigin(btVector3(posX, posY, posZ));

			//Asignamos rotacion
			transform.setRotation(btQuaternion(rotX, rotY, rotZ));

			state.reset (new btDefaultMotionState(transform));
		}
	
		virtual ~Rigid_Body() = default;

		//Getter del rigidbody
		btRigidBody * get ()
		{
			return body.get();
		}
};