#pragma once

#include "GUIToolKit.hpp"
#include "GUIObject.hpp"
#include "GUIText.hpp"

namespace GUI
{

    class Label : public Object
    {
    protected:
        Text* text;
        Alignment alignment;

        //Закрытые методы
        virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

        //Кастомное обновление трансформации
        virtual void customUpdateTransform();
    public:
        //Конструкторы
        Label(sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White, 
                AlignmentType horizontalAligment = AlignmentType::Horizontal_Center, 
                AlignmentType verticalAligment = AlignmentType::Vertical_Center);
        Label(const sf::Vector2f& pos, const sf::Vector2u& size, 
                sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White,
                AlignmentType horizontalAligment = AlignmentType::Horizontal_Center, 
                AlignmentType verticalAligment = AlignmentType::Vertical_Center);
        Label(float x, float y, uint32_t width, uint32_t height, 
                sf::String text = "", const sf::Font* font = nullptr, sf::Color color = sf::Color::White,
                AlignmentType horizontalAligment = AlignmentType::Horizontal_Center, 
                AlignmentType verticalAligment = AlignmentType::Vertical_Center);

        //Методы
        virtual const Alignment& getAligment() const;
        virtual void setAligment(AlignmentType horizontalAligment, AlignmentType verticalAligment);

        //Text

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

        virtual const sf::Vector2f& getTextGlobalPosition() const;
        virtual const sf::Vector2f& getTextLocalPosition() const;
        virtual const sf::Vector2u& getTextSize() const;
        virtual const sf::Vector2f& getTextOrigin() const;
        virtual float getTextRotation() const;

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

        virtual void setTextSize(const sf::Vector2u& size);
        virtual void setTextSize(uint32_t width, uint32_t height);
        virtual void setTextOrigin(const sf::Vector2f& origin);
        virtual void setTextOrigin(float x, float y);
        virtual void setTextRotation(float angle);

        //Методы
        virtual sf::Vector2f findCharacterPos(sf::Uint32 index) const;
    };
}