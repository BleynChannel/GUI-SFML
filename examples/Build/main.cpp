#include <iostream>

#include <GUI/GUI.hpp>

GUI::Button* createButton(float x, float y, uint32_t width, uint32_t height, const std::string& text)
{
	GUI::Button* button = new GUI::Button(x, y, width, height, 
										  sf::Color::White, sf::Color(0x2D2D2DFF), 
										  text);

	button->setHoverMode(true);
	button->setSwitchMode(true);

	button->getText()->setCharacterSize(16);

	button->setBackgroundPressedColor(sf::Color(0x880000FF));
	button->setTextPressedColor(sf::Color::White);
	button->setBackgroundHoverColor(sf::Color(0xC8C8C8FF));
	button->setTextHoverColor(sf::Color(0x5A5A5AFF));
	button->setBackgroundHoverPressedColor(sf::Color(0xA30000FF));
	button->setTextHoverPressedColor(sf::Color(0xE8E8E8FF));

	return button;
}

void buildUI(GUI::Workspace* workspace)
{
	uint32_t columnCount = 1;
	uint32_t rowCount = 3;
	
    auto* layout = workspace->addChild(
		//Background
		new GUI::Panel(50.f, 50.f, 200U, 200U, sf::Color::Grey))->addChild(
		//Layout
		new GUI::Layout(0.f, 0.f, 200U, 200U, columnCount, rowCount));
		
	layout->autoResize(true);
		
	for (uint32_t j = 0U; j < columnCount; j++)
	{
		for (uint32_t k = 0U; k < rowCount; k++)
		{
			layout->setAlignment(j, k, GUI::AlignmentType::Horizontal_Center, GUI::AlignmentType::Vertical_Center);
	
			layout->setPositionObject(j, k, 
				layout->addChild(createButton(0.f, 0.f, 150U, 50U, "Button " + std::to_string((j*k) + 1U))));
		}
	}
}

int main()
{
    //SFML initialization

    sf::RenderWindow window(sf::VideoMode(800, 600), "Example build objects");
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