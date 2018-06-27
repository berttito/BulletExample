/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Sensor
*  @brief: clase sensor, implementa un trigger a partir de una shape y un body. 
*/
#pragma once

#include <memory>
#include "Shape.hpp"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

class Sensor
{
protected:

	//Body
	std::unique_ptr< btGhostObject 		  > body;

	//Shape
	std::shared_ptr< Shape   			  > shape;


public:

	Sensor()
	{
	}

	//Constructor
	Sensor(std::shared_ptr< Shape > & shape, float posX = 0, float posY = 0, float posZ = 0) : shape(shape)
	{
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(posX, posY, posZ));		

		body.reset(new btGhostObject());
		
		body->setCollisionShape(shape.get()->get());
		body->setWorldTransform(transform);
		body->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

	}

	virtual ~Sensor() = default;

	//Getter del body
	btGhostObject * get()
	{
		return body.get();
	}
	
};

