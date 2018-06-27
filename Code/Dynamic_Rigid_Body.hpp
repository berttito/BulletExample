/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Dynamic_Rigid_Body
*  @brief: Clase dynamic rigibody, hereda de rigid_body-
*  Representa el cuerpo fisico dinámico de un objeto.
*  Posee una shape y una masa
*/

#pragma once

#include <memory>
#include "Rigid_Body.hpp"

class Dynamic_Rigid_Body : public Rigid_Body
{		
	//Masa del cuerpo
	btScalar mass;
		
	public:
		
		//Constructor
		Dynamic_Rigid_Body(std::shared_ptr< Shape > & shape, float mass, float posX = 0, float posY = 0, float posZ = 0, float rotX = 0, float rotY = 0, float rotZ = 0) : Rigid_Body(shape, posX, posY, posZ, rotX, rotY, rotZ), mass(btScalar(mass))
		{
			btVector3 localInertia(0, 0, 0);

			shape->get ()->calculateLocalInertia (mass, localInertia);
			
			btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get()->get(), localInertia);
			
			body.reset (new btRigidBody(info));

			body->setActivationState(DISABLE_DEACTIVATION);
		}
};