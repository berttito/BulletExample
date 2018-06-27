/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

#pragma once
#include "Tank_Entity.hpp"

Tank_Entity::Tank_Entity(BulletScene & scene) : Entity(scene)
{

	//BODIES DE LOS TANQUES
	shared_ptr< Shape  > tank_body_shape1(new Box_Shape(0.4f, 0.2f, 0.4f));
	shared_ptr< Rigid_Body > tank_body_collider1(new  Dynamic_Rigid_Body(tank_body_shape1, 5, 13, 3, 0));
	add_body("body_tank1", "../../../../assets/box2.obj", tank_body_collider1, 1.f);

	body_tank = &bodies["body_tank1"];

	/////////

	shared_ptr< Shape  > tank_body_shape2(new Box_Shape(0.2f, 0.2f, 0.2f));
	shared_ptr< Rigid_Body > tank_body_collider2(new Dynamic_Rigid_Body(tank_body_shape2, 20, 13, 3.15, 0));
	add_body("body_tank2", "../../../../assets/box.obj", tank_body_collider2, 1.f);

	body_tank2 = &bodies["body_tank2"];

	////////

	//RUEDAS 

	shared_ptr< Shape  > wheel0_shape1(new Sphere_Shape(0.2));
	shared_ptr< Rigid_Body > wheel0_body_collider1(new Dynamic_Rigid_Body(wheel0_shape1, 5, 13, 2, 0.4));
	add_body("wheel0", "../../../../assets/sphere.obj", wheel0_body_collider1, 1);

	wheel0 = &bodies["wheel0"];
	wheel0->rigid_body.get()->get()->setFriction(20);

	///////

	shared_ptr< Shape  > wheel1_shape1(new Sphere_Shape(0.2));
	shared_ptr< Rigid_Body > wheel1_body_collider1(new Dynamic_Rigid_Body(wheel1_shape1, 5, 13.65, 2, 0.4));
	add_body("wheel1", "../../../../assets/sphere.obj", wheel1_body_collider1, 1);

	wheel1 = &bodies["wheel1"];
	wheel1->rigid_body.get()->get()->setFriction(20);

	///////

	shared_ptr< Shape  > wheel2_shape1(new Sphere_Shape(0.2));
	shared_ptr< Rigid_Body > wheel2_body_collider1(new Dynamic_Rigid_Body(wheel2_shape1, 5, 13.4, 2, -0.12));
	add_body("wheel2", "../../../../assets/sphere.obj", wheel2_body_collider1, 1);

	wheel2 = &bodies["wheel2"];
	wheel2->rigid_body.get()->get()->setFriction(20);

	///////

	shared_ptr< Shape  > wheel3_shape1(new Sphere_Shape(0.2));
	shared_ptr< Rigid_Body > wheel3_body_collider1(new Dynamic_Rigid_Body(wheel3_shape1, 5, 13.62, 2, -0.12));
	add_body("wheel3", "../../../../assets/sphere.obj", wheel3_body_collider1, 1);

	wheel3 = &bodies["wheel3"];
	wheel3->rigid_body.get()->get()->setFriction(20);

	///////

	//JOINTS

	add_revolute_joint("wheelJoint1", tank_body_collider1, wheel0_body_collider1, btVector3(-0.35, -0.5, 0.5), btVector3(0, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1));
	add_revolute_joint("wheelJoint2", tank_body_collider1, wheel1_body_collider1, btVector3(0.35, -0.5, 0.5), btVector3(0, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1));
	add_revolute_joint("wheelJoint3", tank_body_collider1, wheel2_body_collider1, btVector3(-0.35, -0.5, -0.5), btVector3(0, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1));
	add_revolute_joint("wheelJoint4", tank_body_collider1, wheel3_body_collider1, btVector3(0.35, -0.5, -0.5), btVector3(0, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1));

	add_revolute_joint("turretJoint", tank_body_collider1, tank_body_collider2, btVector3(0, 0.5, 0), btVector3(0, 0, 0), btVector3(0, 1, 0), btVector3(0, 1, 0));
}

void Tank_Entity::moveUp()
{
	btVector3 forwardVector = getDirectionVector("body_tank1");

	bodies["wheel0"].rigid_body->get()->applyTorqueImpulse(forwardVector * 0.5);
	bodies["wheel1"].rigid_body->get()->applyTorqueImpulse(forwardVector * 0.5);
	bodies["wheel2"].rigid_body->get()->applyTorqueImpulse(forwardVector * 0.5);
	bodies["wheel3"].rigid_body->get()->applyTorqueImpulse(forwardVector * 0.5);
}

void Tank_Entity::moveDown()
{
	btVector3 forwardVector = getDirectionVector("body_tank1");

	bodies["wheel0"].rigid_body->get()->applyTorqueImpulse(forwardVector * -0.5);
	bodies["wheel1"].rigid_body->get()->applyTorqueImpulse(forwardVector * -0.5);
	bodies["wheel2"].rigid_body->get()->applyTorqueImpulse(forwardVector * -0.5);
	bodies["wheel3"].rigid_body->get()->applyTorqueImpulse(forwardVector * -0.5);
}

void Tank_Entity::moveLeft()
{
	btVector3 forwardVector = getDirectionVector("body_tank1");

	bodies["wheel0"].rigid_body->get()->applyTorqueImpulse(forwardVector * 2);
	bodies["wheel1"].rigid_body->get()->applyTorqueImpulse(forwardVector * -2);
	bodies["wheel2"].rigid_body->get()->applyTorqueImpulse(forwardVector * 2);
	bodies["wheel3"].rigid_body->get()->applyTorqueImpulse(forwardVector * -2);
}

void Tank_Entity::moveRight()
{
	btVector3 forwardVector = getDirectionVector("body_tank1");

	bodies["wheel0"].rigid_body->get()->applyTorqueImpulse(forwardVector * -2);
	bodies["wheel1"].rigid_body->get()->applyTorqueImpulse(forwardVector * 2);
	bodies["wheel2"].rigid_body->get()->applyTorqueImpulse(forwardVector * -2);
	bodies["wheel3"].rigid_body->get()->applyTorqueImpulse(forwardVector * 2);
}

void Tank_Entity::delay()
{
	timer++;
	if (timer >= timeToShoot)
	{
		canShoot = true;
		timer = 0;
	}
}

void Tank_Entity::Shoot()
{
	canShoot = false;
	//Creamos la bala
	shared_ptr< Shape  > bullet_shape(new Box_Shape(0.1f, 0.1f, 0.1f));
	shared_ptr< Rigid_Body > bullet_body_collider(new Dynamic_Rigid_Body(bullet_shape, 1, 13.5, 2, 0));

	add_body("bullet" + std::to_string(contadorBullets), "../../../../assets/item.obj", bullet_body_collider, 1.f);
	bullet = &bodies["bullet" + std::to_string(contadorBullets)];

	//Ponemos el punto de spawn
	btVector3  spawnPoint = bodies["body_tank2"].rigid_body->get()->getWorldTransform().getOrigin();
	bodies["bullet" + std::to_string(contadorBullets)].rigid_body->get()->getWorldTransform().setOrigin(spawnPoint + getDirectionVector("body_tank2"));

	//Le damos fuerza
	btVector3 forceVector = getDirectionVector("body_tank2") * 2500;
	bodies["bullet" + std::to_string(contadorBullets)].rigid_body->get()->applyForce(forceVector, btVector3(0, 0, 0));

	contadorBullets++;
}