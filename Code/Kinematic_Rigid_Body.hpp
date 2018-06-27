
// Comentario de cabecera

#pragma once

#include <memory>
#include "Rigid_Body.hpp"


class Kinematic_Rigid_Body : public Rigid_Body
{
public:

	Kinematic_Rigid_Body(std::shared_ptr< Shape > shape, float posX = 0, float posY = 0, float posZ = 0, float rotX = 0, float rotY = 0, float rotZ = 0) : Rigid_Body(shape, posX, posY, posZ, rotX, rotY, rotZ)
	{
		body.get()->setLinearFactor(btVector3(1, 0, 1));
		body.get()->setAngularFactor(btVector3(0, 0, 0));
		
		btRigidBody::btRigidBodyConstructionInfo info(0, state.get(), shape.get()->get());

		body.reset(new btRigidBody(info));
	}

};