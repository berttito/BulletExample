/*
Author: Alberto Quesada Ibáñez
Date: 27/05/2018
Info:
*/

/**
*  @class: Item_Entity
*  @brief: item_entity, engloba el item y los elementos a los que afecta´la acción de recogerlo.
*  Además implementa las acciones de quitar la puerta y mover la plataforma
*/

#pragma once

#include "Entity.hpp"
#include "Box_Shape.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"

class Item_Entity : public Entity
{
	Body * item;
	Body * door;
	Body * platform;

	//Comprobar el movimiento
	bool move;
	
public:

	//Constructor
	Item_Entity(BulletScene & scene);
	

	void update() override;
	
};