/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

#pragma once

#include <Model_Obj.hpp>
#include "Entity.hpp"
#include "BulletScene.hpp"
#include <memory>
#include <string>
#include <list>

void Entity::add_body(const string & name, const string & model_obj_path, shared_ptr< Rigid_Body > & physics_body, float scale)
{
	Body & body = bodies[name];

	//Creamos el modelo
	body.model_obj.reset(new Model_Obj(model_obj_path));
	body.rigid_body = physics_body;
	body.scale = scale;
	
	// cargar modelo OBJ y añadirlo al render_node de scene
	scene->add_model_obj(name, body.model_obj);
	// añadir el rigid_body al physics_world con o sin máscara (según mask sea 0 o distinto de 0)
	if (mask == 0)
	{
		scene->add_rigid_body(physics_body);
	}
	else
	{
		scene->add_rigid_body(physics_body);
	}	
}

void Entity::add_joints() 
{
	//Recorremos la lista de joints y los vamos incorporando al mundo físico
	for(auto & joint : hinges)
	{		
		scene->getPhysicsWorld().add_constraint(joint.second);		
	}
}

void Entity::add_sensors()
{
	//Recorremos la lista de sensores y los vamos incorporando al mundo físico
	for (auto & sensor : sensors)
	{
		scene->getPhysicsWorld().add_sensor(sensor.second);		
	}
}

void Entity::update()
{
	btTransform physics_transform;

	//copiar el transform de fisica a graficos de todos los Body
	for (auto & body : bodies)
	{		
		body.second.rigid_body.get()->get()->getMotionState()->getWorldTransform(physics_transform);

		glm::mat4 graphics_transform;

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		body.second.model_obj->set_transformation(graphics_transform);

		body.second.model_obj->scale(body.second.scale);
	}
}

btVector3 Entity:: getDirectionVector(const std::string & name)
{
	//cogemos el transform de lo que le pasamos
	btTransform transform = bodies[name].rigid_body->get()->getWorldTransform();
	//creamos una matriz auxiliar donde guardamos la matriz de opengl
	btScalar aux_matrix[16];
	transform.getOpenGLMatrix(aux_matrix);
	//cogemos el vector forward
	return btVector3(aux_matrix[8], aux_matrix[9], aux_matrix[10]);
}


void Entity::apply_force()
{

}


void Entity::delay()
{

}