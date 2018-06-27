/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

#pragma once
#include "Item_Entity.hpp"

Item_Entity::Item_Entity(BulletScene & scene) : Entity(scene)
{
	move = false;

	shared_ptr< Shape  > door_body_shape(new Box_Shape(0.2, 1.6, 2));
	shared_ptr< Rigid_Body > door_body_collider(new Static_Rigid_Body(door_body_shape, 4.5, 2, 0.4));
	add_body("door", "../../../../assets/door.obj", door_body_collider, 1.f);

	door = &bodies["door"];

	///////

	shared_ptr< Shape  > item_body_shape(new Box_Shape(0.1, 0.1, 0.1));
	shared_ptr< Rigid_Body > item_body_collider(new Static_Rigid_Body(item_body_shape, 12, 0.75, 1.3));
	add_body("item", "../../../../assets/item.obj", item_body_collider, 1.f);

	item = &bodies["item"];

	///////

	shared_ptr< Shape  > platform_body_shape(new Box_Shape(1.f, 0.2f, 1.f));
	shared_ptr< Rigid_Body > platform_body_collider(new Dynamic_Rigid_Body(platform_body_shape, 10, 9, 0, 0));

	platform_body_collider->get()->setLinearFactor(btVector3(1, 0, 1));
	platform_body_collider->get()->setAngularFactor(btVector3(0, 0, 0));

	add_body("platform", "../../../../assets/platform.obj", platform_body_collider, 1);

	platform = &bodies["platform"];

	///////

	shared_ptr<Shape> sensor_shape(new Box_Shape(0.1, 0.1, 0.1));
	shared_ptr<Sensor> sensor_body(new Sensor(sensor_shape, 12, 0.9, 1.3));
	add_sensor("sensorKey", sensor_body);

}

void Item_Entity::update()
{
	//Si se puede mover, movemos la plataforma
	if (move)
	{
		btTransform transform = platform->rigid_body->get()->getWorldTransform();

		if (transform.getOrigin().getX() <= 7)
		{
			bodies["platform"].rigid_body->get()->setLinearVelocity(btVector3(0.5, 0, 0));
		}
		else if (transform.getOrigin().getX() >= 9)
		{
			bodies["platform"].rigid_body->get()->setLinearVelocity(btVector3(-0.5, 0, 0));
		}
	}


	//Recorremos los objetos que overlapean con el sensor
	for (int i = 0; i < sensors["sensorKey"]->get()->getNumOverlappingObjects(); i++)
	{
		btRigidBody *overlappedRigidbody = static_cast<btRigidBody *>(sensors["sensorKey"]->get()->getOverlappingObject(i));
		std::cout << sensors["sensorKey"]->get()->getNumOverlappingObjects();

		//Movemos la plataforma
		move = true;

		//Hacemos desaparecer el item y la puerta
		item->rigid_body->get()->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		item->model_obj->set_visible(false);

		door->rigid_body->get()->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		door->model_obj->set_visible(false);

	}

	Entity::update();
}
	