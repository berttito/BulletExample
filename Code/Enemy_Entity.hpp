/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Enemy_Entity
*  @brief: enemy_entity, representan los enemigos que hay que disparar.
*  Construye toda su estructura.
*/


#pragma once

#include "Entity.hpp"
#include "Box_Shape.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"

class Enemy_Entity : public Entity
{
	Body * enemy1;
	Body * enemy2;
	Body * enemy3;

public:

	Enemy_Entity(BulletScene & scene, int mask = 0) : Entity(scene, mask)
	{
		// crear los rigid bodies y añadirlos a las listas de Entity
		
		shared_ptr< Shape  > enemy_body_shape1(new Box_Shape(0.4f, 1.4f, 0.4f));
		shared_ptr< Rigid_Body > enemy_body_collider1(new Dynamic_Rigid_Body(enemy_body_shape1, 5, -3, 3, 0.5));
		add_body("enemy1", "../../../../assets/enemy.obj", enemy_body_collider1, 1.f);

		enemy1 = &bodies["enemy1"];

		//////////

		shared_ptr< Shape  > enemy_body_shape2(new Box_Shape(0.4f, 1.4f, 0.4f));
		shared_ptr< Rigid_Body > enemy_body_collider2(new Dynamic_Rigid_Body(enemy_body_shape2, 5, -3, 3, -1));
		add_body("enemy2", "../../../../assets/enemy.obj", enemy_body_collider2, 1.f);

		enemy2 = &bodies["enemy2"];

		////////////

		shared_ptr< Shape  > enemy_body_shape3(new Box_Shape(0.4f, 1.4f, 0.4f));
		shared_ptr< Rigid_Body > enemy_body_collider3(new Dynamic_Rigid_Body(enemy_body_shape3, 5, -3, 3, 2));
		add_body("enemy3", "../../../../assets/enemy.obj", enemy_body_collider3, 1.f);

		enemy3 = &bodies["enemy3"];
	}
};