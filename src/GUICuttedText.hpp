#pragma once

#include "GUIText.hpp"

namespace GUI
{

    class CuttedText : public Text
    {
    protected:
        //Кастомное обновление трансформации
        virtual void customUpdateTransform() override;
    public:
        //Конструктор
        CuttedText(sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White);
        CuttedText(const sf::Vector2f& pos, const sf::Vector2u& size, 
                   sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White);
        CuttedText(float x, float y, uint32_t width, uint32_t height, 
                   sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White);

        //Text
        virtual void setString(const sf::String& string);
        virtual void setFont(const sf::Font& font);
        virtual void setCharacterSize(size_t size);
        virtual void setLetterSpacing(float spacingFactor);
        virtual void setStyle(sf::Uint32 style);
        virtual void setOutlineThickness(float thickness);
    };
}