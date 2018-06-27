/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Tank_Entity
*  @brief: tank_entity, representa al objeto del tanque.
*  Construye toda su estructura, incorpora los joints necesarios y crea las balas que dispara.
*/

#pragma once

#include "Entity.hpp"
#include "Box_Shape.hpp"
#include "Sphere_Shape.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"

class Tank_Entity : public Entity 
{
	//Cuerpos
	Body * body_tank;
	Body * body_tank2;

	//Ruedas
	Body * wheel0;
	Body * wheel1;
	Body * wheel2;
	Body * wheel3;

	//Balas
	Body * bullet;

	//Comprobamos si se puede disparar
	bool canShoot = true;
	
	//Timer auxiliar para disparar
	float timer = 0;

	//Cada cuanto se puede disparar
	float timeToShoot = 50;

	//Contador de balas
	int contadorBullets = 0;

public:

	//Constructor
	Tank_Entity(BulletScene & scene);

	//Mover hacia delante
	void moveUp();	

	//Mover hacia atrás
	void moveDown();	

	//Mover hacia la izquierda
	void moveLeft();
	
	//Mover hacia la derecha
	void moveRight();
	
	//Rotar torreta hacia la derecha
	void rotateTurretRight() 
	{				
		bodies["body_tank2"].rigid_body->get()->applyTorqueImpulse(btVector3(0, -0.25f, 0));
	}
	
	//Rotar torreta hacia la izquierda
	void rotateTurretLeft() 
	{
		bodies["body_tank2"].rigid_body->get()->applyTorqueImpulse(btVector3(0, 0.25f, 0));
	}

	//Comprobar si se puede disparar
	bool getCanShoot()
	{
		return canShoot;
	}	

	//Delay del disparo
	void delay() override;
	
	//Comprobamos el delay constantemente
	void update() override
	{
		delay();
		Entity::update();
	}

	//Método para disparar
	void Shoot();
	
};