#include <iostream>

#include <GUI/GUIWorkspace.hpp>
#include <GUI/GUIPanel.hpp>

void buildUI(GUI::Workspace* workspace)
{
	//Create panel
	auto* panel = (GUI::Panel*)workspace->addChild(
        new GUI::Panel(50.f, 50.f, 100U, 100U, sf::Color::Green)
    );

    //Creating animation for panel

    panel->createAnimation(
        [&panel](const Animation& animation)
        {
            auto color = panel->getColor();
            color.a--;
            panel->setColor(color);
        }
    );
}

int main()
{
    //SFML initialization

    sf::RenderWindow window(sf::VideoMode(800, 600), "Example GUI::Animation");
    sf::Event event;

    //GUI initialization

    GUI::Application application;
    auto* workspace = new GUI::Workspace(window);
	
	buildUI(workspace);

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