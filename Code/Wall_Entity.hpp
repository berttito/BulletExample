/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Wall_Entity
*  @brief: wall_entity, representan las paredes laterales de la puerta.
*  Construye toda su estructura.
*/


#pragma once

#include "Entity.hpp"
#include "Box_Shape.hpp"
#include "Static_Rigid_Body.hpp"

class Wall_Entity : public Entity
{
	Body * wall;
	Body * wall2;

public:

	Wall_Entity(BulletScene & scene, int mask = 0) : Entity(scene, mask)
	{
		// crear los rigid bodies y añadirlos a las listas de Entity
		
		shared_ptr< Shape  > wall_body_shape(new Box_Shape(0.2f, 1.6f, 0.2f));
		shared_ptr< Rigid_Body > wall_body_collider(new Static_Rigid_Body(wall_body_shape, 4.5, 2, 2.75f));
		add_body("wall", "../../../../assets/wall.obj", wall_body_collider, 1.f);

		wall = &bodies["wall"];

		//////////

		shared_ptr< Shape  > wall_body_shape2(new Box_Shape(0.2f, 1.6f, 0.2f));
		shared_ptr< Rigid_Body > wall_body_collider2(new Static_Rigid_Body(wall_body_shape2, 4.5, 2, -2));
		add_body("wall2", "../../../../assets/wall.obj", wall_body_collider2, 1.f);

		wall2 = &bodies["wall2"];
	}
};