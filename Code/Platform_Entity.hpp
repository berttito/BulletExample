// Comentario de cabecera

#pragma once

#include "Entity.hpp"
#include "Box_Shape.hpp"
#include "Dynamic_Rigid_Body.hpp"


class Platform_Entity : public Entity
{
	Body * platform;	

public:

	Platform_Entity(BulletScene & scene, int mask = 0) : Entity(scene, mask)
	{
		// crear los rigid bodies y las joints y añadirlos a las listas de Entity		
		shared_ptr< Shape  > platform_body_shape(new Box_Shape(1.f, 0.2f, 1.f));
		shared_ptr< Rigid_Body > platform_body_collider(new Dynamic_Rigid_Body(platform_body_shape, 1, 7, 0, 0));

		platform_body_collider->get()->setLinearFactor(btVector3(1, 0, 1));
		platform_body_collider->get()->setAngularFactor(btVector3(0, 0, 0));

		add_body("platform", "../../../../assets/platform.obj", platform_body_collider, 1);

		platform = &bodies["platform"];
		
	}

	void apply_force() override
	{
		btTransform transform = platform->rigid_body->get()->getWorldTransform();		

		if(transform.getOrigin().getX() <= 7)
		{
			bodies["platform"].rigid_body->get()->setLinearVelocity(btVector3(0.8, 0, 0));
		}
		else if(transform.getOrigin().getX() >= 9)
		{
			bodies["platform"].rigid_body->get()->setLinearVelocity(btVector3(-0.8, 0, 0));
		}

	}

	void update() override
	{
		apply_force();
		Entity::update();
	}
};