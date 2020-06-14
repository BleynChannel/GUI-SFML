#pragma once

#include "GUIContainer.hpp"

namespace GUI
{

    class Workspace : public Container
    {
    private:
        sf::Clock* clock;
        Animation* animation;

        //Закрытые методы
        void setBorder(bool onBorder);
    public:
        //Конструктор/Деструктор
        Workspace(sf::RenderTarget& target);
        Workspace(sf::RenderTarget& target, const sf::Vector2f& pos, const sf::Vector2u& size);
        Workspace(sf::RenderTarget& target, float x, float y, uint32_t width, uint32_t height);
        ~Workspace();

        //Методы
        void handleInput() override;
        void handleEvent(const sf::Event& event) override;
        void update();
        void update(float dt) override;
        void render();
    };
}