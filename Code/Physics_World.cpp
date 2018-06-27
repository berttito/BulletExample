/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

#pragma once
#include "Physics_World.hpp"

void Physics_World::add(std::shared_ptr< Rigid_Body > & body)
{
	bodies.push_back(body);

	world->addRigidBody(body->get());
}

void Physics_World::add_constraint(std::shared_ptr< btTypedConstraint > joint)
{
	joints.push_back(joint);
	btTypedConstraint  * pointer = joint.get();

	world->addConstraint(pointer);
}

void Physics_World::add_sensor(std::shared_ptr< Sensor > sensor_aux)
{
	sensors.push_back(sensor_aux);
	btGhostObject  * pointer = sensor_aux->get();

	world->addCollisionObject(pointer);

	world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
}

void Physics_World::add_with_mask(std::shared_ptr< Rigid_Body > & body, int mask)
{
	bodies.push_back(body);

	world->addRigidBody(body->get());
}