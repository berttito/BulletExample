/*
Author: Alberto Quesada Ib��ez
Date: 27/05/2018
Info:
*/

/**
*  @class: Graphic_Scene
*  @brief: Clase graphic_scene, representa la escena gr�fica.
*  Encapsula el mundo gr�fico del proyecto
*  Contiene m�todos propios de configuraci�n de la escena gr�fica.
*/

#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>


class Graphic_Scene
{
	//Referencia al render node que dibuja la escena gr�fica
	std::shared_ptr< glt::Render_Node > scene;

public:

	//Constructor
	Graphic_Scene()
	{
		//Creamos la escena
		create_scene();		
	}

	std::shared_ptr< glt::Render_Node > create_scene()
	{
		// Se crean los elementos (nodos) y la escena a la que se a�adir�n:
		scene.reset(new glt::Render_Node);
		
		std::shared_ptr< glt::Camera      > camera(new glt::Camera(20.f, 1.f, 50.f, 1.f));
		std::shared_ptr< glt::Light       > light(new glt::Light);

		// Se a�aden los nodos a la escena:		
		scene->add("camera", camera);
		scene->add("light", light);

		return scene;
	}

	//Configuraci�n de la escena
	void configure_scene(glt::Render_Node & scene)
	{
		scene["light"]->translate(glt::Vector3(10.f, 10.f, 10.f));
		scene["camera"]->translate(glt::Vector3(0.f, 0.f, 5.f));
	}

	void reset_viewport(const sf::Window & window, glt::Render_Node & scene)
	{
		GLsizei width = GLsizei(window.getSize().x);
		GLsizei height = GLsizei(window.getSize().y);

		scene.get_active_camera()->set_aspect_ratio(float(width) / height);

		glViewport(0, 0, width, height);
	}
};