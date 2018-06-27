/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

#pragma once

#include "BulletScene.hpp"

void BulletScene::add_game_object(const std::string & name, std::shared_ptr<Entity> & game_object)
{
	//Añadimos el gameobject
	game_objects[name] = game_object;

	//Añadimos los joints
	game_objects[name]->add_joints();

	//Añadimos los sensores
	game_objects[name]->add_sensors();
}

void BulletScene::add_game_object_with_mask(const std::string & name, std::shared_ptr<Entity> & game_object, int group, int mask)
{
	//Añadimos el gameobject
	game_objects[name] = game_object;

	//Añadimos los joints
	game_objects[name]->add_joints();

	//Añadimos los sensores
	game_objects[name]->add_sensors();
}

void BulletScene::create_scene()
{
	// Se crean los elementos (nodos) y la escena a la que se añadirán:
	std::shared_ptr< glt::Camera > camera(new glt::Camera(20.f, 1.f, 50.f, 1.f));
	std::shared_ptr< glt::Light  > light(new glt::Light);

	// Se añaden los nodos a la escena:
	graphics_scene.add("camera", camera);
	graphics_scene.add("light", light);

	graphics_scene["light"]->translate(glt::Vector3(10.f, 10.f, 10.f));
	graphics_scene["camera"]->translate(glt::Vector3(17.f, 4.f, 6.f));
	graphics_scene["camera"]->rotate_around_y(1.f);
}

void BulletScene::reset_viewport(const sf::Window & window, glt::Render_Node & scene)
{
	GLsizei width = GLsizei(window.getSize().x);
	GLsizei height = GLsizei(window.getSize().y);

	scene.get_active_camera()->set_aspect_ratio(float(width) / height);

	glViewport(0, 0, width, height);
}