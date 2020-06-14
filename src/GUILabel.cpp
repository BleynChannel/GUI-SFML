#include "GUILabel.hpp"

//Закрытые методы

void GUI::Label::render(sf::RenderTarget& target, sf::RenderStates states) const
{
    drawObject(text, target, states);
}

//Кастомное обновление методов

void GUI::Label::customUpdateTransform()
{
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

//Конструкторы

GUI::Label::Label(sf::String text, const sf::Font* font, sf::Color color, 
                  AlignmentType horizontalAligment, AlignmentType verticalAligment)
    : text(new Text(text, font, color)), alignment(horizontalAligment, verticalAligment)
{
    connectObject(this->text);
}

GUI::Label::Label(const sf::Vector2f& pos, const sf::Vector2u& size, 
                  sf::String text, const sf::Font* font, sf::Color color,
                  AlignmentType horizontalAligment, AlignmentType verticalAligment)
    : Object(pos, size), text(new Text(text, font, color)), alignment(horizontalAligment, verticalAligment)
{
    connectObject(this->text);
}

GUI::Label::Label(float x, float y, uint32_t width, uint32_t height, 
                  sf::String text, const sf::Font* font, sf::Color color,
                  AlignmentType horizontalAligment, AlignmentType verticalAligment)
    : Object(x, y, width, height), text(new Text(text, font, color)), alignment(horizontalAligment, verticalAligment)
{
    connectObject(this->text);
}

//Методы

const GUI::Alignment& GUI::Label::getAligment() const
{
    return alignment;
}

void GUI::Label::setAligment(AlignmentType horizontalAligment, AlignmentType verticalAligment)
{
    alignment.horizontal = horizontalAligment;
    alignment.vertical = verticalAligment;

    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

//Text

//Геттеры

const sf::String& GUI::Label::getString() const
{
    return text->getString();
}

const sf::Font* GUI::Label::getFont() const
{
    return text->getFont();
}

size_t GUI::Label::getCharacterSize() const
{
    return text->getCharacterSize();
}

float GUI::Label::getLetterSpacing() const
{
    return text->getLetterSpacing();
}

float GUI::Label::getLineSpacing() const
{
    return text->getLineSpacing();
}

sf::Uint32 GUI::Label::getStyle() const
{
    return text->getStyle();
}

const sf::Color& GUI::Label::getColor() const
{
    return text->getColor();
}

const sf::Color& GUI::Label::getOutlineColor() const
{
    return text->getOutlineColor();
}

float GUI::Label::getOutlineThickness() const
{
    return text->getOutlineThickness();
}

const sf::Vector2f& GUI::Label::getTextGlobalPosition() const
{
    return text->getGlobalPosition();
}

const sf::Vector2f& GUI::Label::getTextLocalPosition() const
{
    return text->getLocalPosition();
}

const sf::Vector2u& GUI::Label::getTextSize() const
{
    return text->getSize();
}

const sf::Vector2f& GUI::Label::getTextOrigin() const
{
    return text->getOrigin();
}

float GUI::Label::getTextRotation() const
{
    return text->getRotation();
}

//Сеттеры

void GUI::Label::setString(const sf::String& string)
{
    text->setString(string);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setFont(const sf::Font& font)
{
    text->setFont(font);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setCharacterSize(size_t size)
{
    text->setCharacterSize(size);
    text->setPosition(alignment.getCoordinates(localPos, this->size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setLineSpacing(float spacingFactor)
{
    text->setLineSpacing(spacingFactor);
}

void GUI::Label::setLetterSpacing(float spacingFactor)
{
    text->setLetterSpacing(spacingFactor);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setStyle(sf::Uint32 style)
{
    text->setStyle(style);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setColor(const sf::Color& color)
{
    text->setColor(color);
}

void GUI::Label::setOutlineColor(const sf::Color& color)
{
    text->setOutlineColor(color);
}

void GUI::Label::setOutlineThickness(float thickness)
{
    text->setOutlineThickness(thickness);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setTextSize(const sf::Vector2u& size)
{
    text->setSize(size);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setTextSize(uint32_t width, uint32_t height)
{
    text->setSize(width, height);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setTextOrigin(const sf::Vector2f& origin)
{
    text->setOrigin(origin);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setTextOrigin(float x, float y)
{
    text->setOrigin(x, y);
    text->setPosition(alignment.getCoordinates(localPos, size, text->getSize()) + text->getOrigin());
}

void GUI::Label::setTextRotation(float angle)
{
    text->setRotation(angle);
}

//Методы

sf::Vector2f GUI::Label::findCharacterPos(sf::Uint32 index) const
{
    return text->findCharacterPos(index);
}
