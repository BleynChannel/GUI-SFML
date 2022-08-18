#include "CustomObject.hpp"

void CustomObject::handleInput()
{
	
}

GUI::Button* CustomObject::createButton(float x, float y, uint32_t width, uint32_t height)
{
	GUI::Button* button = new GUI::Button(x, y, width, height, 
										  sf::Color::White, sf::Color(0x2D2D2DFF), 
										  "Button " + std::to_string(countButton++));

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

CustomObject::CustomObject(GUI::Workspace* workspace)
	: Container(sf::Vector2f(0.f, 0.f), workspace->getSize()), countButton(1U)
{
	resize = true;

    mainPanel = (GUI::Panel*)addChild(new GUI::Panel(sf::Vector2f(0.f, 0.f), getSize(), sf::Color(0x2D2D2DFF)));
	mainPanel->autoResize(true);

	layout = (GUI::Layout*)addChild(new GUI::Layout(sf::Vector2f(0.f, 0.f), getSize(), 3U, 2U));
	layout->autoResize(true);

	((GUI::Button*)layout->setPositionObject(0U, 0U, layout->addChild(createButton(0.f, 0.f, 150U, 50U))))->setOnTouch(
		[this](GUI::BaseButton* button, int, int)
		{
			if (button->getPressed())
				layout->setAlignment(0U, 0U, GUI::AlignmentType::Horizontal_Right, GUI::AlignmentType::Vertical_Top);
			else
				layout->setAlignment(0U, 0U, GUI::AlignmentType::Horizontal_Center, GUI::AlignmentType::Vertical_Center);
		}
	);

	GUI::Button* directionButton_1 = (GUI::Button*)layout->setPositionObject(1U, 0U, layout->addChild(createButton(0.f, 0.f, 150U, 50U)));
	GUI::Button* directionButton_2 = (GUI::Button*)layout->setPositionObject(1U, 0U, layout->addChild(createButton(0.f, 0.f, 150U, 50U)));

	directionButton_1->setSwitchMode(false);
	directionButton_2->setSwitchMode(false);

	directionButton_1->setOnTouch(
		[this](GUI::BaseButton*, int, int)
		{
			layout->setDirection(1U, 0U, GUI::Direction::Horizontal);
		}
	);

	directionButton_2->setOnTouch(
		[this](GUI::BaseButton*, int, int)
		{
			layout->setDirection(1U, 0U, GUI::Direction::Vertical);
		}
	);

	GUI::Button* spacingButton = (GUI::Button*)layout->setPositionObject(2U, 0U, layout->addChild(createButton(0.f, 0.f, 150U, 50U)));
	layout->setPositionObject(2U, 0U, layout->addChild(createButton(0.f, 0.f, 150U, 50U)));
	layout->setPositionObject(2U, 0U, layout->addChild(createButton(0.f, 0.f, 150U, 50U)));

	spacingButton->setOnTouch(
		[this](GUI::BaseButton* button, int, int)
		{
			if (button->getPressed())
				layout->setSpacing(2U, 0U, 15U);
			else
				layout->setSpacing(2U, 0U, 1U);
		}
	);

	GUI::Button* marginButton_1 = (GUI::Button*)layout->setPositionObject(0U, 1U, layout->addChild(createButton(0.f, 0.f, 110U, 50U)));
	GUI::Button* marginButton_2 = (GUI::Button*)layout->setPositionObject(0U, 1U, layout->addChild(createButton(0.f, 0.f, 110U, 50U)));

	layout->setAlignment(0U, 1U, GUI::AlignmentType::Horizontal_Left, GUI::AlignmentType::Vertical_Bottom);
	layout->setDirection(0U, 1U, GUI::Direction::Horizontal);

	marginButton_1->setSwitchMode(false);
	marginButton_2->setSwitchMode(false);

	marginButton_1->setOnTouch(
		[this](GUI::BaseButton*, int, int)
		{
			layout->setMargin(0U, 1U, 20U, 20U);
		}
	);

	marginButton_2->setOnTouch(
		[this](GUI::BaseButton*, int, int)
		{
			layout->setMargin(0U, 1U, 0U, 0U);
		}
	);

	GUI::Button* fittingButton = (GUI::Button*)layout->setPositionObject(1U, 1U, layout->addChild(createButton(0.f, 0.f, 150U, 50U)));

	fittingButton->setOnTouch(
		[this](GUI::BaseButton* button, int, int)
		{
			if (button->getPressed())
				layout->setFitting(1U, 1U, true, true);
			else {
				layout->setFitting(1U, 1U, false, false);
				button->setSize(150U, 50U);
			}
		}
	);

	GUI::Button* posButton_1 = (GUI::Button*)layout->setPositionObject(2U, 1U, layout->addChild(createButton(0.f, 0.f, 150U, 50U)));
	GUI::Object* posButton_2 = layout->setPositionObject(2U, 1U, layout->addChild(createButton(0.f, 0.f, 150U, 50U)));

	posButton_1->setOnTouch(
		[this, posButton_2](GUI::BaseButton* button, int, int)
		{
			if (button->getPressed())
				layout->setPositionObject(0U, 0U, posButton_2);
			else
				layout->setPositionObject(2U, 1U, posButton_2);
		}
	);
}

CustomObject::~CustomObject()
{
	auto& childs = layout->getChildrens();
	while (!childs.empty())
		delete childs.back();

	delete layout;
	delete mainPanel;
}