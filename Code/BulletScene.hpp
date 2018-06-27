/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Bullet_Scene
*  @brief: Clase bullet_scene, auna la escena gráfica con la física.
*  Encapsula el mundo gráfico del proyecto.
*  Contiene métodos propios de configuración de la escena gráfica.
*  Contiene eventos de teclado.
*/

#pragma once

#include <memory>
#include <map>
#include <iostream>
#include <string>

#include <Render_Node.hpp>
#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>

#include "Physics_World.hpp"
#include "Entity.hpp"
#include "Tank_Entity.hpp"
#include "Ground_Entity.hpp"
#include "Wall_Entity.hpp"
#include "Door_Entity.hpp"
#include "Item_Entity.hpp"
#include "Enemy_Entity.hpp"
#include "Platform_Entity.hpp"



class BulletScene
{
	protected:
	
	//Mapa de todos los gameobjects de la escena
	std::map <std::string, std::shared_ptr<Entity>> game_objects;	

	//Referencia a la escena gráfica que se construye a partir del Render_node
	glt::Render_Node graphics_scene;

	//Referencia al mundo físico 
	Physics_World    physics_world;

	public:

	BulletScene() 
	{
		//Creamos la escena
		create_scene();

		//Añadimos uno a uno todos los gameobjects que va a tener la escena
		add_game_object("ground", shared_ptr< Entity >(new Ground_Entity(*this)));
		add_game_object("tank", shared_ptr< Entity >(new Tank_Entity(*this)));		
		add_game_object("enemies", shared_ptr< Entity >(new Enemy_Entity(*this)));
		add_game_object("wall", shared_ptr< Entity >(new Wall_Entity(*this)));		
		add_game_object("item", shared_ptr< Entity >(new Item_Entity(*this)));		
	}

	public:

	//Metodo para añadir los gameobject, sus joints y sus sensores
	void add_game_object(const std::string & name, std::shared_ptr<Entity> & game_object);
	

	//Metodo para añadir los gameobject, sus joints y sus sensores con su correspondiente grupo y mascara
	void add_game_object_with_mask(const std::string & name, std::shared_ptr<Entity> & game_object, int group, int mask);	
	
	//Getter del physics world
	Physics_World & getPhysicsWorld()
	{
		return physics_world;
	}

	//Getter de la escena gráfica
	glt::Render_Node & getGraphicScene()
	{
		return graphics_scene;
	}

	//Creamos la escena
	void create_scene();
	
	//Añadimos el modelo a la escena gráfica
    void add_model_obj(const string & name, shared_ptr< Model_Obj > & model)
    {
        graphics_scene.add(name, model);
    }

	//Añadimos el rigidbody al mundo físico
	void add_rigid_body(shared_ptr< Rigid_Body > & physics_body) 
	{
		physics_world.add(physics_body);
	}

	//Añadimos el rigidbody al mundo físico con su correspondiente máscara
	void add_rigid_body(shared_ptr< Rigid_Body > & physics_body, int mask)
	{
		physics_world.add_with_mask(physics_body, mask);
	}

	//Añadimos el joint al mundo físico
	void add_joint(shared_ptr <btTypedConstraint> joint)
	{		
		physics_world.add_constraint(joint);		
	}

	//Metodo para resetear el viewport
	void reset_viewport(const sf::Window & window, glt::Render_Node & scene);

	
	//Getter de cualquier gameobject de la escena
	Entity *get_game_object(const std::string & name)
	{
		//Si lo encuentra retorna un puntero o sino retorna null
		if (game_objects.count(name))
		{
			return game_objects[name].get();
		}
		else
		{
			return nullptr;
		}
	}

	//Si nos movemos para delante
	void upKeyPressed()
	{
		Tank_Entity * tank = dynamic_cast<Tank_Entity *>(get_game_object("tank"));

		if (tank)
		{
			tank->moveUp();
		}
	}

	//Si nos movemos para atrás
	void downKeyPressed()
	{
		Tank_Entity * tank = dynamic_cast<Tank_Entity *>(get_game_object("tank"));

		if (tank)
		{
			tank->moveDown();			
		}
	}

	//Si nos movemos a la izquierda
	void leftKeyPressed()
	{
		Tank_Entity * tank = dynamic_cast<Tank_Entity *>(get_game_object("tank"));

		if (tank)
		{
			tank->moveLeft();			
		}
	}

	//Si nos movemos a la derecha
	void rightKeyPressed()
	{
		Tank_Entity * tank = dynamic_cast<Tank_Entity *>(get_game_object("tank"));

		if (tank)
		{
			tank->moveRight();
		}
	}
	
	//Si rotamos la torreta a la derecha
	void rotateRight() 
	{
		Tank_Entity * tank = dynamic_cast<Tank_Entity *>(get_game_object("tank"));

		if (tank)
		{
			tank->rotateTurretRight();					
		}
	}

	//Si rotamos la torreta a la izquierda
	void rotateLeft()
	{
		Tank_Entity * tank = dynamic_cast<Tank_Entity *>(get_game_object("tank"));

		if (tank)
		{
			tank->rotateTurretLeft();
		}
	}

	//Si disparamos
	void shoot()
	{
		Tank_Entity * tank = dynamic_cast<Tank_Entity *>(get_game_object("tank"));

		if (tank->getCanShoot())
		{
			tank->Shoot();
		}
	}

	//Update de la escena y de todos los gameobjects
	void update()
	{
		physics_world.step(1.f / 60.f);
		
		//Actualizacion de todas las entidades	
		for (auto & game_object : game_objects) 
		{
			game_object.second->update();
		}	
	}

	//Llama al render de graphics_scene
	void render()
	{
		graphics_scene.render();
	}
};