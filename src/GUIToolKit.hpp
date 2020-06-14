#pragma once

//Игровые заголовки
#include <SFML/Graphics.hpp>

namespace GUI
{

    //Direction

    enum class Direction : bool
    {
        Horizontal,
        Vertical
    };

    //SizePolicy

    enum class SizePolicy : bool
    {
        Absolute,
        Relative
    };

    //Aligment

    enum class AlignmentType : short 
    {
        Horizontal_Left,
        Horizontal_Center,
        Horizontal_Right,
        Vertical_Top,
        Vertical_Center,
        Vertical_Bottom
    };

    struct Alignment
    {
        AlignmentType horizontal, vertical;

        Alignment() : horizontal(AlignmentType::Horizontal_Center), vertical(AlignmentType::Vertical_Center) {}
        Alignment(AlignmentType horizontal, AlignmentType vertical) : horizontal(horizontal), vertical(vertical) {}

        sf::Vector2f getCoordinates(float x, float y, uint32_t width1, uint32_t height1, uint32_t width2, uint32_t height2);
        sf::Vector2f getCoordinates(const sf::Vector2f& pos, const sf::Vector2u& size1, const sf::Vector2u& size2);
    };

    sf::Vector2f getAlignmentCoordinates(float x, float y, uint32_t width1, uint32_t height1, uint32_t width2, uint32_t height2,
                                         AlignmentType horizontalAligment, AlignmentType verticalAligment);
    sf::Vector2f getAlignmentCoordinates(const sf::Vector2f& pos, const sf::Vector2u& size1, const sf::Vector2u& size2,
                                         AlignmentType horizontalAligment, AlignmentType verticalAligment);

    //Margin

    struct Margin
    {
        uint32_t horizontal, vertical;

        Margin() : horizontal(0U), vertical(0U) {}
        Margin(uint32_t horizontal, uint32_t vertical) : horizontal(horizontal), vertical(vertical) {}

        sf::Vector2f getCoordinates(float x, float y, AlignmentType horizontalAligment, AlignmentType verticalAligment);
        sf::Vector2f getCoordinates(const sf::Vector2f& pos, AlignmentType horizontalAligment, AlignmentType verticalAligment);
    };

    sf::Vector2f getMarginCoordinates(float x, float y, AlignmentType horizontalAligment, AlignmentType verticalAligment, 
                                      uint32_t horizontalMargin, uint32_t verticalMargin);
    sf::Vector2f getMarginCoordinates(const sf::Vector2f& pos, AlignmentType horizontalAligment, AlignmentType verticalAligment, 
                                      uint32_t horizontalMargin, uint32_t verticalMargin);

    //Fitting

    struct Fitting
    {
        bool horizontal, vertical;
        uint32_t horizontalOffset, verticalOffset;

        Fitting() : horizontal(false), vertical(false), horizontalOffset(0), verticalOffset(0) {}
        Fitting(bool horizontal, bool vertical, uint32_t horizontalOffset = 0U, uint32_t verticalOffset = 0U) 
            : horizontal(horizontal), vertical(vertical), horizontalOffset(horizontalOffset), verticalOffset(verticalOffset) {}
        
        sf::FloatRect getObjectRect(float x1, float y1, uint32_t width1, uint32_t height1, 
                                    float x2, float y2, uint32_t width2, uint32_t height2);
    };

    sf::FloatRect getFittingObjectRect(float x1, float y1, uint32_t width1, uint32_t height1, 
                                       float x2, float y2, uint32_t width2, uint32_t height2,
                                       bool horizontalFitting, bool verticalFitting,
                                       uint32_t horizontalFittingOffset = 0U, uint32_t verticalFittingOffset = 0U);

    //Color Transition
    sf::Color getColorTransition(const sf::Color& color1, const sf::Color& color2, float position);
}