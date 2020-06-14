#include "GUICuttedText.hpp"

//Кастомное обновление трансформации

void GUI::CuttedText::customUpdateTransform()
{
    const sf::FloatRect& bounds = text.getLocalBounds();
    text.setPosition(-bounds.left, -bounds.top);

    const sf::FloatRect& normalizeBounds = text.getLocalBounds();

    text.setScale(static_cast<uint32_t>(normalizeBounds.width) ? (size.x / normalizeBounds.width) : 0.f,
                        static_cast<uint32_t>(normalizeBounds.height) ? (size.y / normalizeBounds.height) : 0.f);

    size.x = static_cast<uint32_t>(normalizeBounds.width) ? size.x : 0U;
    size.y = static_cast<uint32_t>(normalizeBounds.height) ? size.y : 0U;
}

//Конструктор

GUI::CuttedText::CuttedText(sf::String text, const sf::Font* font, sf::Color color)
    : Text(text, font, color)
{
    const sf::FloatRect& bounds = this->text.getLocalBounds();
    setSize(static_cast<uint32_t>(bounds.width), static_cast<uint32_t>(bounds.height));
}

GUI::CuttedText::CuttedText(const sf::Vector2f& pos, const sf::Vector2u& size, sf::String text, const sf::Font* font, sf::Color color)
    : Text(pos, size, text, font, color) 
{
    setSize(size);
}

GUI::CuttedText::CuttedText(float x, float y, uint32_t width, uint32_t height, sf::String text, const sf::Font* font, sf::Color color)
    : Text(x, y, width, height, text, font, color) 
{
    setSize(size);
}

//Text

void GUI::CuttedText::setString(const sf::String& string)
{
    text.setString(string.isEmpty() ? " " : string);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.width), static_cast<uint32_t>(bounds.height));
}

void GUI::CuttedText::setFont(const sf::Font& font)
{
    text.setFont(font);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.width), static_cast<uint32_t>(bounds.height));
}

void GUI::CuttedText::setCharacterSize(size_t size)
{
    text.setCharacterSize(size);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.width), static_cast<uint32_t>(bounds.height));
}

void GUI::CuttedText::setLetterSpacing(float spacingFactor)
{
    text.setLetterSpacing(spacingFactor);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.width), static_cast<uint32_t>(bounds.height));
}

void GUI::CuttedText::setStyle(sf::Uint32 style)
{
    text.setStyle(style);

	const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.width), static_cast<uint32_t>(bounds.height));
}

void GUI::CuttedText::setOutlineThickness(float thickness)
{
    text.setOutlineThickness(thickness);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.width), static_cast<uint32_t>(bounds.height));
}