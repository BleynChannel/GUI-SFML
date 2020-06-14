#include "GUIPanel.hpp"

//Закрытые методы

void GUI::Panel::render(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = texture;

    target.draw(panel, states);
}

//Кастомное обновление трансформации

void GUI::Panel::customUpdateTransform()
{
    panel[1].position = sf::Vector2f(static_cast<float>(size.x), 0.f);
    panel[2].position = sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
    panel[3].position = sf::Vector2f(0.f, static_cast<float>(size.y));

    for (uint32_t i = 1U; i < 4U; i++)
        panel[i].texCoords = panel[i].position;
}

//Конструктор

GUI::Panel::Panel(sf::Color color) 
    : panel(sf::PrimitiveType::Quads, 4), color(color), texture(nullptr)
{
    panel[0].position = sf::Vector2f(0.f, 0.f);
    customUpdateTransform();

    for (uint32_t i = 0U; i < 4; i++)
        panel[i].color = color;
}

GUI::Panel::Panel(const sf::Vector2f& pos, const sf::Vector2u& size, sf::Color color)
    : Object(pos, size), panel(sf::PrimitiveType::Quads, 4), color(color), texture(nullptr)
{
    panel[0].position = sf::Vector2f(0.f, 0.f);
    customUpdateTransform();

    for (uint32_t i = 0U; i < 4; i++)
        panel[i].color = color;
}

GUI::Panel::Panel(float x, float y, uint32_t width, uint32_t height, sf::Color color)
    : Object(x, y, width, height), panel(sf::PrimitiveType::Quads, 4), color(color), texture(nullptr)
{
    panel[0].position = sf::Vector2f(0.f, 0.f);
    customUpdateTransform();

    for (uint32_t i = 0U; i < 4; i++)
        panel[i].color = color;
}

GUI::Panel::Panel(sf::Texture& texture)
    : Object(), panel(sf::PrimitiveType::Quads, 4), texture(&texture)
{
    panel[0].position = sf::Vector2f(0.f, 0.f);
    customUpdateTransform();
}

GUI::Panel::Panel(const sf::Vector2f& pos, const sf::Vector2u& size, sf::Texture& texture)
    : Object(pos, size), panel(sf::PrimitiveType::Quads, 4), texture(&texture)
{
    panel[0].position = sf::Vector2f(0.f, 0.f);
    customUpdateTransform();
}

GUI::Panel::Panel(float x, float y, uint32_t width, uint32_t height, sf::Texture& texture)
    : Object(x, y, width, height), panel(sf::PrimitiveType::Quads, 4), texture(&texture)
{
    panel[0].position = sf::Vector2f(0.f, 0.f);
    customUpdateTransform();
}

//Методы

//Геттеры

const sf::Color& GUI::Panel::getColor() const
{
    return color;
}

std::vector<sf::Color> GUI::Panel::getGradient() const
{
    std::vector<sf::Color> array;
    for (uint32_t i = 0U; i < 4; i++)
        array[i] = panel[i].color;

    return array;
}

const sf::Texture* GUI::Panel::getTexture() const
{
    return texture;
}

//Сеттеры

void GUI::Panel::setColor(const sf::Color& color)
{
    this->color = color;

    for (uint32_t i = 0U; i < 4; i++)
        panel[i].color = color;
}

void GUI::Panel::setGradient(const sf::Color& point1, const sf::Color& point2, const sf::Color& point3, const sf::Color& point4)
{
    panel[0].color = point1;
    panel[1].color = point2;
    panel[2].color = point3;
    panel[3].color = point4;
}

void GUI::Panel::setTexture(sf::Texture& texture)
{
    this->texture = &texture;
}

void GUI::Panel::setGradient(const std::vector<sf::Color>& array)
{
    for (uint32_t i = 0U; i < 4; i++)
        panel[i].color = array[i];
}
