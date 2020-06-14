#pragma once

#include "GUIObject.hpp"

namespace GUI
{

    class Panel : public Object
    {
    protected:
        sf::VertexArray panel;
        sf::Color color;
        sf::Texture* texture;

        //Закрытые методы
        virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

        //Кастомное обновление трансформации
        virtual void customUpdateTransform() override;
    public:
        //Конструктор
        Panel(sf::Color color = sf::Color::White);
        Panel(const sf::Vector2f& pos, const sf::Vector2u& size, sf::Color color = sf::Color::White);
        Panel(float x, float y, uint32_t width, uint32_t height, sf::Color color = sf::Color::White);
        Panel(sf::Texture& texture);
        Panel(const sf::Vector2f& pos, const sf::Vector2u& size, sf::Texture& texture);
        Panel(float x, float y, uint32_t width, uint32_t height, sf::Texture& texture);

        //Методы

        //Геттеры
        virtual const sf::Color& getColor() const;
        virtual std::vector<sf::Color> getGradient() const;
        virtual const sf::Texture* getTexture() const;

        //Сеттеры
        virtual void setColor(const sf::Color& color);
        virtual void setGradient(const std::vector<sf::Color>& array);
        virtual void setGradient(const sf::Color& point1, const sf::Color& point2, const sf::Color& point3, const sf::Color& point4);
        virtual void setTexture(sf::Texture& texture);
    };
}