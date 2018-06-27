/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Static_Rigid_Body
*  @brief: Clase static rigibody, hereda de rigid_body.
*  Representa el cuerpo fisico estático de un objeto.
*  Posee una shape
*/

#pragma once

#include <memory>
#include "Rigid_Body.hpp"


class Static_Rigid_Body : public Rigid_Body
{
		
	public:
		
		//Constructor
		Static_Rigid_Body(std::shared_ptr< Shape > shape, float posX = 0, float posY = 0, float posZ = 0, float rotX = 0, float rotY = 0, float rotZ = 0) : Rigid_Body(shape, posX, posY, posZ, rotX, rotY, rotZ)
		{
			btRigidBody::btRigidBodyConstructionInfo info (0, state.get (), shape.get()->get());
			
			body.reset (new btRigidBody(info));
		}
		
};