#pragma once

#include "GUIPanel.hpp"
#include "GUICuttedText.hpp"

namespace GUI
{

    class BaseButton : public Object
    {
    protected:
        Panel* panel;
        CuttedText* text;

        uint32_t marginText;
        sf::String string;

        bool isMousePressed;

        std::function<void(BaseButton*, int, int)> onTouch;
        bool pressed;
        bool hover;
        bool switchMode;
        bool hoverMode;

        bool animatedPressed;
        float animationPressedDuration;
        bool animatedHover;
        float animationHoverDuration;

        //Закрытые методы
        virtual void handleEvent(const sf::Event& event) override;
        virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

        //Кастомные методы
        virtual void customSetSize(const sf::Vector2u& size) override;
        virtual void customSetSize(uint32_t width, uint32_t height) override;

        //Кастомное обновление трансформации
        virtual void customUpdateTransform();
    public:
        //Конструкторы
        BaseButton(sf::String text = "", const sf::Font* font = nullptr);
        BaseButton(const sf::Vector2f& pos, const sf::Vector2u& size, sf::String text = "", const sf::Font* font = nullptr);
        BaseButton(float x, float y, uint32_t width, uint32_t height, sf::String text = "", const sf::Font* font = nullptr);

        //Геттеры
        virtual const std::function<void(BaseButton*, int, int)>& getOnTouch() const;
        virtual bool getPressed() const;
        virtual bool getHover() const;
        virtual bool getSwitchMode() const;
        virtual bool getHoverMode() const;
        virtual uint32_t getMarginText() const;
        virtual bool getAnimatedPressed() const;
        virtual float getAnimationPressedDuration() const;
        virtual bool getAnimatedHover() const;
        virtual float getAnimationHoverDuration() const;

        //Сеттеры
        virtual void setOnTouch(const std::function<void(BaseButton*, int, int)>& onTouch);
        virtual void setSwitchMode(bool switchMode);
        virtual void setHoverMode(bool hoverMode);
        virtual void setMarginText(uint32_t marginText);
        virtual void setAnimatedPressed(bool animated);
        virtual void setAnimationPressedDuration(float duration);
        virtual void setAnimatedHover(bool animated);
        virtual void setAnimationHoverDuration(float duration);

        //Методы
        virtual void createAnimation(const std::function<void(const Animation&)> frameHandle, 
                                     const std::function<void()>& onFinish = nullptr) override;
        virtual void changeAnimation(uint32_t index, const std::function<void(const Animation&)> frameHandle, 
                                     const std::function<void()>& onFinish = nullptr) override;
        virtual void removeAnimation(uint32_t index);
    };
}