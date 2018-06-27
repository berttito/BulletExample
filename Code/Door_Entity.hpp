
// Comentario de cabecera

#pragma once

#include "Entity.hpp"
#include "Box_Shape.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"

class Door_Entity : public Entity
{
	Body * door;

public:

	Door_Entity(BulletScene & scene, int mask = 0) : Entity(scene, mask)
	{
		// crear los rigid bodies y las joints y añadirlos a las listas de Entity
				
		shared_ptr< Shape  > door_body_shape(new Box_Shape(0.2, 1.6, 2));
		shared_ptr< Rigid_Body > door_body_collider(new Static_Rigid_Body(door_body_shape, 4.5, 2, 0.4));
		add_body("door", "../../../../assets/door.obj", door_body_collider, 1.f);

		door = &bodies["door"];
	}
};