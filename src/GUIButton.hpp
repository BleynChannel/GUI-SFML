#pragma once

#include "GUIBaseButton.hpp"
#include "GUIToolKit.hpp"

namespace GUI
{

    class Button : public BaseButton
    {
    private:
        const sf::Color* currentBackgroundColor;
        const sf::Color* currentTextColor;
    protected:
        sf::Color* backgroundColor;
        sf::Color* backgroundPressedColor;
        sf::Color* backgroundHoverColor;
        sf::Color* backgroundHoverPressedColor;
        sf::Color* backgroundDisabledColor;

        sf::Color* textColor;
        sf::Color* textPressedColor;
        sf::Color* textHoverColor;
        sf::Color* textHoverPressedColor;
        sf::Color* textDisabledColor;

        //Закрытые методы
        virtual void handleEvent(const sf::Event& event) override;
    public:
        //Конструкторы/Деструктор
        Button(const sf::Color& backgroundColor = sf::Color::White, const sf::Color& textColor = sf::Color::Black,
               sf::String text = "", const sf::Font* font = nullptr);

        Button(const sf::Color& backgroundColor, const sf::Color& textColor,
               const sf::Color& backgroundDisabledColor, const sf::Color& textDisabledColor,
               sf::String text = "", const sf::Font* font = nullptr);

        Button(const sf::Vector2f& pos, const sf::Vector2u& size,
               const sf::Color& backgroundColor = sf::Color::White, const sf::Color& textColor = sf::Color::Black,
               sf::String text = "", const sf::Font* font = nullptr);

        Button(const sf::Vector2f& pos, const sf::Vector2u& size,
              const sf::Color& backgroundColor, const sf::Color& textColor,
              const sf::Color& backgroundDisabledColor, const sf::Color& textDisabledColor,
              sf::String text = "", const sf::Font* font = nullptr);

        Button(float x, float y, uint32_t width, uint32_t height,
               const sf::Color& backgroundColor = sf::Color::White, const sf::Color& textColor = sf::Color::Black,
               sf::String text = "", const sf::Font* font = nullptr);

        Button(float x, float y, uint32_t width, uint32_t height,
               const sf::Color& backgroundColor, const sf::Color& textColor,
               const sf::Color& backgroundDisabledColor, const sf::Color& textDisabledColor,
               sf::String text = "", const sf::Font* font = nullptr);

        virtual ~Button();

        //Геттеры
        virtual const sf::Color* getBackgroundColor() const;
        virtual const sf::Color* getTextColor() const;
        virtual const sf::Color* getBackgroundPressedColor() const;
        virtual const sf::Color* getTextPressedColor() const;
        virtual const sf::Color* getBackgroundHoverColor() const;
        virtual const sf::Color* getBackgroundHoverPressedColor() const;
        virtual const sf::Color* getTextHoverColor() const;
        virtual const sf::Color* getTextHoverPressedColor() const;
        virtual const sf::Color* getBackgroundDisabledColor() const;
        virtual const sf::Color* getTextDisabledColor() const;

        //Сеттеры
        virtual void setAnimatedPressed(bool animated) override;
        virtual void setAnimatedHover(bool animated) override;
        virtual void setBackgroundColor(const sf::Color& color);
        virtual void setTextColor(const sf::Color& color);
        virtual void setBackgroundPressedColor(const sf::Color& color);
        virtual void setTextPressedColor(const sf::Color& color);
        virtual void setBackgroundHoverColor(const sf::Color& color);
        virtual void setBackgroundHoverPressedColor(const sf::Color& color);
        virtual void setTextHoverColor(const sf::Color& color);
        virtual void setTextHoverPressedColor(const sf::Color& color);
        virtual void setBackgroundDisabledColor(const sf::Color& color);
        virtual void setTextDisabledColor(const sf::Color& color);

        virtual void setDisabled(bool disabled) override;

        //Text

        //Геттеры
        virtual const sf::String& getTextString() const;
        virtual const sf::Font* getTextFont() const;
        virtual size_t getTextCharacterSize() const;
        virtual float getTextLetterSpacing() const;
        virtual float getTextLineSpacing() const;
        virtual sf::Uint32 getTextStyle() const;
        virtual const sf::Color& getTextOutlineColor() const;
        virtual float getTextOutlineThickness() const;

        //Сеттеры
        virtual void setTextString(const sf::String& string);
        virtual void setTextFont(const sf::Font& font);
        virtual void setTextCharacterSize(size_t size);
        virtual void setTextLineSpacing(float spacingFactor);
        virtual void setTextLetterSpacing(float spacingFactor);
        virtual void setTextStyle(sf::Uint32 style);
        virtual void setTextOutlineColor(const sf::Color& color);
        virtual void setTextOutlineThickness(float thickness);

        virtual void setTextSize(const sf::Vector2u& size);
        virtual void setTextSize(uint32_t width, uint32_t height);
        virtual void setTextRotation(float angle);

        //Методы
        virtual void textScale(const sf::Vector2i& scaled);
        virtual void textScale(int scaledX, int scaledY);
        virtual void textRotate(float angle);

        //Методы
        virtual sf::Vector2f findTextCharacterPos(sf::Uint32 index) const;
    };
}