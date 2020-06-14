#include "GUIText.hpp"

sf::Font* GUI::Text::standartfont = nullptr;
uint32_t GUI::Text::countText = 0U;

//Закрытые методы

void GUI::Text::render(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

//Кастомное обновление трансформации

void GUI::Text::customUpdateTransform()
{
    const sf::FloatRect& normalizeBounds = text.getLocalBounds();

    text.setScale(static_cast<uint32_t>(normalizeBounds.left + normalizeBounds.width) ? 
                    (size.x / (normalizeBounds.left + normalizeBounds.width)) : 0.f,
                  static_cast<uint32_t>(normalizeBounds.top + normalizeBounds.height) ? 
                    (size.y / (normalizeBounds.top + normalizeBounds.height)) : 0.f);

    size.x = static_cast<uint32_t>(normalizeBounds.left + normalizeBounds.width) ? size.x : 0U;
    size.y = static_cast<uint32_t>(normalizeBounds.top + normalizeBounds.height) ? size.y : 0U;
}

//Конструктор/Деструктор

GUI::Text::Text(sf::String text, const sf::Font* font, sf::Color color)
{
    if (!countText) {
        standartfont = new sf::Font;
        standartfont->loadFromFile(Application::getPathToStandartFont());
    }

    countText++;

    this->text.setFont(font ? *font : *standartfont);
    this->text.setString(text.isEmpty() ? " " : text);
    this->text.setFillColor(color);
    
    const sf::FloatRect& bounds = this->text.getLocalBounds();
    setSize(static_cast<uint32_t>(bounds.left + bounds.width), static_cast<uint32_t>(bounds.top + bounds.height));
}

GUI::Text::Text(const sf::Vector2f& pos, const sf::Vector2u& size, sf::String text, const sf::Font* font, sf::Color color)
    : Object(pos, size)
{
    if (!countText) {
        standartfont = new sf::Font;
        standartfont->loadFromFile(Application::getPathToStandartFont());
    }

    countText++;

    this->text.setFont(font ? *font : *standartfont);
    this->text.setString(text.isEmpty() ? " " : text);
    this->text.setFillColor(color);

    setSize(size);
}

GUI::Text::Text(float x, float y, uint32_t width, uint32_t height, sf::String text, const sf::Font* font, sf::Color color)
    : Object(x, y, width, height)
{
    if (!countText) {
        standartfont = new sf::Font;
        standartfont->loadFromFile(Application::getPathToStandartFont());
    }

    countText++;

    this->text.setFont(font ? *font : *standartfont);
    this->text.setString(text.isEmpty() ? " " : text);
    this->text.setFillColor(color);

    setSize(size);
}

GUI::Text::~Text()
{
    if (!(--countText))
        delete standartfont;
}

//Геттеры

const sf::String& GUI::Text::getString() const
{
    return text.getString();
}

const sf::Font* GUI::Text::getFont() const
{
    return text.getFont();
}

size_t GUI::Text::getCharacterSize() const
{
    return text.getCharacterSize();
}

float GUI::Text::getLetterSpacing() const
{
    return text.getLetterSpacing();
}

float GUI::Text::getLineSpacing() const
{
    return text.getLineSpacing();
}

sf::Uint32 GUI::Text::getStyle() const
{
    return text.getStyle();
}

const sf::Color& GUI::Text::getColor() const
{
    return text.getFillColor();
}

const sf::Color& GUI::Text::getOutlineColor() const
{
    return text.getOutlineColor();
}

float GUI::Text::getOutlineThickness() const
{
    return text.getOutlineThickness();
}

//Сеттеры

void GUI::Text::setString(const sf::String& string)
{
    text.setString(string.isEmpty() ? " " : string);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.left + bounds.width), static_cast<uint32_t>(bounds.top + bounds.height));
}

void GUI::Text::setFont(const sf::Font& font)
{
    text.setFont(font);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.left + bounds.width), static_cast<uint32_t>(bounds.top + bounds.height));
}

void GUI::Text::setCharacterSize(size_t size)
{
    text.setCharacterSize(size);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.left + bounds.width), static_cast<uint32_t>(bounds.top + bounds.height));
}

void GUI::Text::setLineSpacing(float spacingFactor)
{
    text.setLetterSpacing(spacingFactor);
}

void GUI::Text::setLetterSpacing(float spacingFactor)
{
    text.setLetterSpacing(spacingFactor);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.left + bounds.width), static_cast<uint32_t>(bounds.top + bounds.height));
}

void GUI::Text::setStyle(sf::Uint32 style)
{
    text.setStyle(style);

	const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.left + bounds.width), static_cast<uint32_t>(bounds.top + bounds.height));
}

void GUI::Text::setColor(const sf::Color& color)
{
    text.setFillColor(color);
}

void GUI::Text::setOutlineColor(const sf::Color& color)
{
    text.setOutlineColor(color);
}

void GUI::Text::setOutlineThickness(float thickness)
{
    text.setOutlineThickness(thickness);

    const sf::FloatRect& bounds = text.getGlobalBounds();
    setSize(static_cast<uint32_t>(bounds.left + bounds.width), static_cast<uint32_t>(bounds.top + bounds.height));
}

//Методы

sf::Vector2f GUI::Text::findCharacterPos(sf::Uint32 index) const
{
    return text.findCharacterPos(index);
}
