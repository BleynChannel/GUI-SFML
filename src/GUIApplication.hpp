#pragma once

//SFML заголовки
#include <SFML/Graphics.hpp>

//Стандартные заголовки
#include <vector>

namespace GUI
{
    class Object;

    class Application
    {
    private:
        static std::vector<Object*>* allObject;

        //Закрытые методы
        static void updateIndex(uint32_t fromIndex);
        static void remove();
    private:
        //Переменные для настроек
        
        //Object
        static bool object_on_border;

        //Text
        static sf::String path_to_standart_font;

        //BaseButton
        static bool button_on_hover_mode;

        static float button_animation_pressed_duration;
        static float button_animation_hover_duration;

        static bool button_on_animation_pressed;
        static bool button_on_animation_hover;

        static uint32_t button_margin_text;

        //Layout
        static uint32_t layout_default_column_count;
        static uint32_t layout_default_row_count;

        static uint32_t layout_default_position_column;
        static uint32_t layout_default_position_row;
    public:
        //Конструктор/Деструктор
        Application();
        virtual ~Application();
    public:
        //Методы для настроек

        //Геттеры
        
        //Object
        static bool getObjectOnBorder();

        //Text
        static const sf::String& getPathToStandartFont();

        //BaseButton
        static bool getButtonOnHoverMode();

        static float getButtonAnimationPressedDuration();
        static float getButtonAnimationHoverDuration();

        static bool getButtonOnAnimationPressed();
        static bool getButtonOnAnimationHover();

        static uint32_t getButtonMarginText();

        //Layout
        static uint32_t getLayoutDefaultColumnCount();
        static uint32_t getLayoutDefaultRowCount();

        static uint32_t getLayoutDefaultPositionColumn();
        static uint32_t getLayoutDefaultPositionRow();

        //Сеттеры

        //Object
        static void setObjectOnBorder(bool on);

        //Text
        static void setPathToStandartFont(const sf::String& path);

        //BaseButton
        static void setButtonOnHoverMode(bool on);

        static void setButtonAnimationPressedDuration(float duration);
        static void setButtonAnimationHoverDuration(float duration);

        static void setButtonOnAnimationPressed(bool on);
        static void setButtonOnAnimationHover(bool on);

        static void setButtonMarginText(uint32_t margin);

        //Layout
        static void setLayoutDefaultColumnCount(uint32_t count);
        static void setLayoutDefaultRowCount(uint32_t count);

        static void setLayoutDefaultPositionColumn(uint32_t position);
        static void setLayoutDefaultPositionRow(uint32_t position);

        friend Object;
    };
}