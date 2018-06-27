/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Graphic_Scene
*  @brief: Clase graphic_scene, representa la escena gráfica.
*  Encapsula el mundo gráfico del proyecto
*  Contiene métodos propios de configuración de la escena gráfica.
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
	//Referencia al render node que dibuja la escena gráfica
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
		// Se crean los elementos (nodos) y la escena a la que se añadirán:
		scene.reset(new glt::Render_Node);
		
		std::shared_ptr< glt::Camera      > camera(new glt::Camera(20.f, 1.f, 50.f, 1.f));
		std::shared_ptr< glt::Light       > light(new glt::Light);

		// Se añaden los nodos a la escena:		
		scene->add("camera", camera);
		scene->add("light", light);

		return scene;
	}

	//Configuración de la escena
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