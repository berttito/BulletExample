/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Entity
*  @brief: Clase entity, es generica a partir de la cual van a heredar distintos tipos
*  de entidades.
*  Contiene métodos para añadir bodies, constraints y sensores al mundo físico.
*/

#pragma once

#include <Model_Obj.hpp>
#include "Rigid_Body.hpp"
#include "Sensor.hpp"
#include <memory>
#include <iostream>
#include <string>
#include <list>


using std::string;
using std::shared_ptr;
using glt::Model_Obj;

class BulletScene;

class Entity
{
protected:

	//Struct de cada objeto:
		//Modelo
		//Rigidbody
		//Escala
    struct Body
    {
        shared_ptr< Model_Obj  > model_obj;
        shared_ptr< Rigid_Body > rigid_body;
        float scale;
    };

	//Lista de bodies
    typedef std::map< string, Body > BodyList;	

	//Lista de constraints
	typedef std::map< string, std::shared_ptr<btHingeConstraint > > HingeList;

	//Lista de sensores
	typedef std::map< std::string, std::shared_ptr<Sensor > > SensorList;

    BodyList      bodies;	
	HingeList	  hinges;
	SensorList    sensors;

	//Referencia a la escena
    BulletScene * scene;

	//Máscara (si es que la tiene)
    int           mask;

public:
	
	//Constructor
	Entity(BulletScene & scene, int mask = 0) : scene(&scene), mask(mask)
	{
	}

	//Método para crear el objeto
	void add_body(const string & name, const string & model_obj_path, shared_ptr< Rigid_Body > & physics_body, float scale);
  
	//Método para crear el joint
	void add_revolute_joint(const std::string & name, const shared_ptr< Rigid_Body > & bodyA, const shared_ptr< Rigid_Body > & bodyB, const btVector3 &pivotInA, const btVector3 &pivotInB, const btVector3 &axisInA, const btVector3 &axisInB, bool useReferenceFrameA = false)
	{
		shared_ptr<btHingeConstraint > & joint = hinges[name];
		joint.reset(new btHingeConstraint(*bodyA->get(), *bodyB->get(), pivotInA, pivotInB, axisInA, axisInB));		
	}

	//Método para crear el sensor
	void add_sensor(const std::string & name, const shared_ptr< Sensor > & sensor_aux)
	{
		shared_ptr<Sensor> & sensor = sensors[name];
		sensor = sensor_aux;
	}

	//Añadir todos los joints
	void add_joints();
	
	//Añadir todos los sensores
	void add_sensors();

	//Update para actualizar la entidad
	virtual void update();

	//Método para aplicar una fuerza si es que algun hijo necesita implementarlo
	virtual void apply_force();

	//Método para aplicar un delay si es que algun hijo necesita implementarlo
	virtual void delay();

	//Método para obtener el vector de direccion del objeto
	btVector3 getDirectionVector(const std::string & name);
	
};