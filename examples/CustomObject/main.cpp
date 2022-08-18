#include <iostream>

#include <GUI/GUI.hpp>
#include "CustomObject.hpp"

int main()
{
    //SFML initialization

    sf::RenderWindow window(sf::VideoMode(800, 600), "Example create custom object");
    sf::Event event;

    //GUI initialization

    GUI::Application application;
	
    auto* workspace = new GUI::Workspace(window);
    new CustomObject(workspace);

    //SFML loop

    while (window.isOpen())
    {
        workspace->handleInput();

        while (window.pollEvent(event))
        {
            workspace->handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        workspace->update();

        window.clear();
        workspace->render();
        window.display();
    }

	return 0;
}