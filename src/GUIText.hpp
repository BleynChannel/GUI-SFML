#pragma once

#include "GUIObject.hpp"

namespace GUI
{

    class Text : public Object
    {
    private:
        static sf::Font* standartfont;
        static uint32_t countText;
    protected:
        sf::Text text;

        //Закрытые методы
        virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

        //Кастомное обновление трансформации
        virtual void customUpdateTransform() override;
    public:
        //Конструктор/Деструктор
        Text(sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White);
        Text(const sf::Vector2f& pos, const sf::Vector2u& size, 
             sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White);
        Text(float x, float y, uint32_t width, uint32_t height, 
             sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White);
        virtual ~Text();

        //Геттеры
        virtual const sf::String& getString() const;
        virtual const sf::Font* getFont() const;
        virtual size_t getCharacterSize() const;
        virtual float getLetterSpacing() const;
        virtual float getLineSpacing() const;
        virtual sf::Uint32 getStyle() const;
        virtual const sf::Color& getColor() const;
        virtual const sf::Color& getOutlineColor() const;
        virtual float getOutlineThickness() const;

        //Сеттеры
        virtual void setString(const sf::String& string);
        virtual void setFont(const sf::Font& font);
        virtual void setCharacterSize(size_t size);
        virtual void setLineSpacing(float spacingFactor);
        virtual void setLetterSpacing(float spacingFactor);
        virtual void setStyle(sf::Uint32 style);
        virtual void setColor(const sf::Color& color);
        virtual void setOutlineColor(const sf::Color& color);
        virtual void setOutlineThickness(float thickness);

        //Методы
        virtual sf::Vector2f findCharacterPos(sf::Uint32 index) const;
    };
}