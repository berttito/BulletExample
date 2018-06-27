/*
Author: Alberto Quesada Ib��ez
Date: 27/05/2018
Info:
*/

/**
*  @class: Physics_World
*  @brief: Clase physics_world, representa el mundo f�sico.
*  Encapsula el mundo f�sico de bullet
*  Contiene m�todos para a�adir bodies, constraints y sensores al mundo f�sico.
*/


#pragma once

#include <memory>
#include <vector>
#include "Rigid_Body.hpp"
#include "Sensor.hpp"
#include <btBulletDynamicsCommon.h>

class Physics_World
{
	//Configuraci�n del mundo f�sico de bullet
	std::unique_ptr<btDiscreteDynamicsWorld> world;
	std::vector< std::shared_ptr< Rigid_Body >> bodies;
	std::vector< std::shared_ptr< btTypedConstraint >> joints;
	std::vector< std::shared_ptr< Sensor >> sensors;

	btDefaultCollisionConfiguration 	collisionConfiguration;
	btCollisionDispatcher 				collisionDispatcher;
	btDbvtBroadphase 					overlappingPairCache;
	btSequentialImpulseConstraintSolver constraintSolver;
	
	//Constructor
	public: 
		Physics_World()  : collisionDispatcher(&collisionConfiguration)
		{
			world.reset 
			(
				new btDiscreteDynamicsWorld 
				(
					&collisionDispatcher,
					&overlappingPairCache,
					&constraintSolver,
					&collisionConfiguration
				)
			);

			world->setGravity(btVector3(0, -10, 0));
		}
		
	public:
	
		//M�todo update para actualizar
		void step(float deltaTime)
		{
			world->stepSimulation(deltaTime);
		}
		
		//M�todo para a�adir bodies al mundo f�sico
		void add(std::shared_ptr< Rigid_Body > & body);
		

		//M�todo para a�adir constraints al mundo f�sico
		void add_constraint(std::shared_ptr< btTypedConstraint > joint);
	

		//M�todo para a�adir sensores al mundo f�sico
		void add_sensor(std::shared_ptr< Sensor > sensor_aux);
		

		//M�todo para a�adir bodies al mundo con una m�scara de colisi�n determinada
		void add_with_mask(std::shared_ptr< Rigid_Body > & body, int mask);
		

		//M�todo para el reset del mundo f�sico
		void reset() 
		{
			world.reset();
		}
}; 