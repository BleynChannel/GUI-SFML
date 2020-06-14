#pragma once

//SFML заголовки
#include <SFML/Graphics.hpp>

//Стандартные заголовки
#include <functional>

namespace GUI
{
    class Object;
    class Container;
    class Workspace;

    struct Animation
    {
    private:
        sf::Clock clock;
        float startTime;
        float currentTime;
    public:
        bool started;
        float duration;
        float position;
        std::function<void(const Animation&)> frameHandle;
        std::function<void()> onFinish;

        //Конструктор
        Animation(const std::function<void(const Animation&)>& frameHandle, const std::function<void()>& onFinish);

        //Методы
        void start(float duration);
        void stop();

        friend Object;
        friend Container;
        friend Workspace;
    };
}