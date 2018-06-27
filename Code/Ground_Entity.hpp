/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Ground_Entity
*  @brief: ground_entity, representa todos los suelos que hay en la escena.
*  Construye toda la estructura.
*/


#pragma once

#include "Entity.hpp"
#include "Box_Shape.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"

class Ground_Entity : public Entity
{
	Body * ground1;
	Body * ground2;
	Body * ground3;
	Body * ground4;
	Body * ground5;

public:

	Ground_Entity(BulletScene & scene, int mask = 0) : Entity(scene, mask)
	{
		// crear los rigid bodies y añadirlos a las listas de Entity

		shared_ptr< Shape  > ground_body_shape1(new Box_Shape(3, 0.2f, 3));
		shared_ptr< Rigid_Body > ground_body_collider1(new Static_Rigid_Body(ground_body_shape1, 13, 0.1, 0));
		add_body("ground1", "../../../../assets/ground.obj", ground_body_collider1, 1.f);

		ground1 = &bodies["ground1"];
		
		////////

		shared_ptr< Shape  > ground_body_shape2(new Box_Shape(3, 0.2f, 3));
		shared_ptr< Rigid_Body > ground_body_collider2(new Static_Rigid_Body(ground_body_shape2, 8, -1, -0.2));
		add_body("ground2", "../../../../assets/ground.obj", ground_body_collider2, 1.f);

		ground2 = &bodies["ground2"];

		//////////

		shared_ptr< Shape  > ground_body_shape3(new Box_Shape(3, 0.2f, 3));
		shared_ptr< Rigid_Body > ground_body_collider3(new Static_Rigid_Body(ground_body_shape3, 3, 0, 0));
		add_body("ground3", "../../../../assets/ground.obj", ground_body_collider3, 1.f);

		ground3 = &bodies["ground3"];

		//////////

		shared_ptr< Shape  > ground_body_shape4(new Box_Shape(3, 0.2f, 3));
		shared_ptr< Rigid_Body > ground_body_collider4(new Static_Rigid_Body(ground_body_shape4, -2, -1, -0.2));
		add_body("ground4", "../../../../assets/ground.obj", ground_body_collider4, 1.f);

		ground4 = &bodies["ground4"];

		////////////

		shared_ptr< Shape  > ground_body_shape5(new Box_Shape(3, 0.2f, 3));
		shared_ptr< Rigid_Body > ground_body_collider5(new Static_Rigid_Body(ground_body_shape5, -5, 0, 0));
		add_body("ground5", "../../../../assets/ground.obj", ground_body_collider5, 1.f);

		ground5 = &bodies["ground5"];
	}
};