/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Physics_World
*  @brief: Clase physics_world, representa el mundo físico.
*  Encapsula el mundo físico de bullet
*  Contiene métodos para añadir bodies, constraints y sensores al mundo físico.
*/


#pragma once

#include <memory>
#include <vector>
#include "Rigid_Body.hpp"
#include "Sensor.hpp"
#include <btBulletDynamicsCommon.h>

class Physics_World
{
	//Configuración del mundo físico de bullet
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
	
		//Método update para actualizar
		void step(float deltaTime)
		{
			world->stepSimulation(deltaTime);
		}
		
		//Método para añadir bodies al mundo físico
		void add(std::shared_ptr< Rigid_Body > & body);
		

		//Método para añadir constraints al mundo físico
		void add_constraint(std::shared_ptr< btTypedConstraint > joint);
	

		//Método para añadir sensores al mundo físico
		void add_sensor(std::shared_ptr< Sensor > sensor_aux);
		

		//Método para añadir bodies al mundo con una máscara de colisión determinada
		void add_with_mask(std::shared_ptr< Rigid_Body > & body, int mask);
		

		//Método para el reset del mundo físico
		void reset() 
		{
			world.reset();
		}
}; 