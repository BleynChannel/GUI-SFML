#include "GUIApplication.hpp"
#include "GUIObject.hpp"

std::vector<GUI::Object*>* GUI::Application::allObject = nullptr;

//Переменные для настроек

//Object

bool GUI::Application::object_on_border = false;

//Text

sf::String GUI::Application::path_to_standart_font = "";

//BaseButton

bool GUI::Application::button_on_hover_mode = false;

float GUI::Application::button_animation_pressed_duration = 1.5f;
float GUI::Application::button_animation_hover_duration = 1.5f;

bool GUI::Application::button_on_animation_pressed = true;
bool GUI::Application::button_on_animation_hover = true;

uint32_t GUI::Application::button_margin_text = 6U;

//Layout

uint32_t GUI::Application::layout_default_column_count = 1U;
uint32_t GUI::Application::layout_default_row_count = 1U;

uint32_t GUI::Application::layout_default_position_column = 0U;
uint32_t GUI::Application::layout_default_position_row = 0U;

//Закрытые методы

void GUI::Application::updateIndex(uint32_t fromIndex)
{
    if (allObject) {
        size_t size = allObject->size();
        for (uint32_t i = fromIndex; i < size; i++)
            (*allObject)[i]->indexObject = i;
    }
}

void GUI::Application::remove()
{
    while (!allObject->empty())
        delete (*allObject)[0];

    delete allObject;
    allObject = nullptr;
}

//Конструктор/Деструктор

GUI::Application::Application()
{
    if (allObject)
        remove();

    allObject = new std::vector<Object*>;
}

GUI::Application::~Application()
{
    remove();
}

//Методы для настроек

//Геттеры

//Object

bool GUI::Application::getObjectOnBorder()
{
    return object_on_border;
}

//Text

const sf::String& GUI::Application::getPathToStandartFont()
{
    return path_to_standart_font;
}

//BaseButton

bool GUI::Application::getButtonOnHoverMode()
{
    return button_on_hover_mode;
}

float GUI::Application::getButtonAnimationPressedDuration()
{
    return button_animation_pressed_duration;
}

float GUI::Application::getButtonAnimationHoverDuration()
{
    return button_animation_hover_duration;
}

bool GUI::Application::getButtonOnAnimationPressed()
{
    return button_on_animation_pressed;
}

bool GUI::Application::getButtonOnAnimationHover()
{
    return button_on_animation_hover;
}

uint32_t GUI::Application::getButtonMarginText()
{
    return button_margin_text;
}

//Layout

uint32_t GUI::Application::getLayoutDefaultColumnCount()
{
    return layout_default_column_count;
}

uint32_t GUI::Application::getLayoutDefaultRowCount()
{
    return layout_default_row_count;
}

uint32_t GUI::Application::getLayoutDefaultPositionColumn()
{
    return layout_default_position_column;
}

uint32_t GUI::Application::getLayoutDefaultPositionRow()
{
    return layout_default_position_row;
}

//Сеттеры

//Object

void GUI::Application::setObjectOnBorder(bool on)
{
    object_on_border = on;
}

//Text

void GUI::Application::setPathToStandartFont(const sf::String& path)
{
    path_to_standart_font = path;
}

//BaseButton

void GUI::Application::setButtonOnHoverMode(bool on)
{
    button_on_hover_mode = on;
}

void GUI::Application::setButtonAnimationPressedDuration(float duration)
{
    button_animation_pressed_duration = duration;
}

void GUI::Application::setButtonAnimationHoverDuration(float duration)
{
    button_animation_hover_duration = duration;
}

void GUI::Application::setButtonOnAnimationPressed(bool on)
{
    button_on_animation_pressed = on;
}

void GUI::Application::setButtonOnAnimationHover(bool on)
{
    button_on_animation_hover = on;
}

void GUI::Application::setButtonMarginText(uint32_t margin)
{
    button_margin_text = margin;
}

//Layout

void GUI::Application::setLayoutDefaultColumnCount(uint32_t count)
{
    layout_default_column_count = count;
}

void GUI::Application::setLayoutDefaultRowCount(uint32_t count)
{
    layout_default_row_count = count;
}

void GUI::Application::setLayoutDefaultPositionColumn(uint32_t position)
{
    layout_default_position_column = position;
}

void GUI::Application::setLayoutDefaultPositionRow(uint32_t position)
{
    layout_default_position_row = position;
}