#include <iostream>

#include <GUI/GUIError.hpp>
#include <GUI/GUIContainer.hpp>

int main()
{
    GUI::Application application;

    try
    {
        auto* container = new GUI::Container;
        auto* child = container->addChild(new GUI::Object, 10); //Error!!!
    }
    catch (const GUI::Error& error) {
        std::cout << error.what() << std::endl;
        
        return 1;
    }

    return 0;
}