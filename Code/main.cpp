/*
    Bullet Continuous Collision Detection and Physics Library
    Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it freely,
    subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
       If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    This is the official 'Hello, World' example cleaned up for additional simplicity and clarity.
*/

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

#include "headers/BulletScene.hpp"


using namespace std;
using namespace glt;

int main ()
{   
    // Se crea la ventana y el contexto de OpenGL asociado a ella:

    sf::Window window
    (
        sf::VideoMode(1920, 1080),
        "Bullet Rigid Bodies",
        sf::Style::Default,
        sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core)      // Se usa OpenGL 3.2 core profile
    );

    // Se determinan las características de OpenGL disponibles en la máquina:

	if (!glt::initialize_opengl_extensions())
	{
		exit (-1);
	}

    // Se activa la sincronización vertical:

    window.setVerticalSyncEnabled (true);

    // Se crea y se configura la escena:
	BulletScene scene;
	   
    // Se inicializan algunos elementos de OpenGL:

	scene.reset_viewport (window, scene.getGraphicScene());

    glClearColor (0.2f, 0.2f, 0.2f, 1.f);

    bool running = true;
    int  frame   = 0;

    do
    {
        // Read the user input:

        sf::Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    running = false;
                    break;
                }

				//Eventos de teclado
				case sf::Event::KeyPressed:
				{
					//Movimiento hacia la izquierda
					if (event.key.code == sf::Keyboard::A)						
						scene.leftKeyPressed();

					//Movimiento hacia la derecha
					if (event.key.code == sf::Keyboard::D)
						scene.rightKeyPressed();

					//Movimiento hacia arriba
					if (event.key.code == sf::Keyboard::W)
						scene.upKeyPressed();

					//Movimiento hacia abajo
					if (event.key.code == sf::Keyboard::S)
						scene.downKeyPressed();

					//Disparo
					if (event.key.code == sf::Keyboard::Space)
						scene.shoot();					

					break;
				}

				case sf::Event::KeyReleased: 
				{
					if (event.key.code == sf::Keyboard::Right)
						scene.rotateRight();

					if (event.key.code == sf::Keyboard::Left)
						scene.rotateLeft();
				}

                case sf::Event::Resized:
                {
                    scene.reset_viewport (window, scene.getGraphicScene());
                    break;
                }
            }
        }

        // Perform the simulation:

		scene.update();

        // Render the scene:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    

        scene.render ();

        window.display ();
    }
    while (running);

    // Se debe destruir el mundo físico antes de que se destruyan los cuerpos rígidos:

	scene.getPhysicsWorld().reset();	

    return EXIT_SUCCESS;
}
