#include "GUIToolKit.hpp"
#include "GUIError.hpp"

//Aligment

sf::Vector2f GUI::Alignment::getCoordinates(float x, float y, uint32_t width1, uint32_t height1, uint32_t width2, uint32_t height2)
{
    sf::Vector2f newPos;

    newPos.x = horizontal == AlignmentType::Horizontal_Center ? x + width1 / 2.f - width2 / 2.f :
              (horizontal == AlignmentType::Horizontal_Right ? x + static_cast<float>(width1 - width2) : 0.f);

    newPos.y = vertical == AlignmentType::Vertical_Center ? y + height1 / 2.f - height2 / 2.f :
              (vertical == AlignmentType::Vertical_Bottom ? y + static_cast<float>(height1 - height2) : 0.f);

    return newPos;
}

sf::Vector2f GUI::Alignment::getCoordinates(const sf::Vector2f& pos, const sf::Vector2u& size1, const sf::Vector2u& size2)
{
    sf::Vector2f newPos;

    newPos.x = horizontal == AlignmentType::Horizontal_Center ? pos.x + size1.x / 2.f - size2.x / 2.f :
              (horizontal == AlignmentType::Horizontal_Right ? pos.x + static_cast<float>(size1.x - size2.x) : 0.f);

    newPos.y = vertical == AlignmentType::Vertical_Center ? pos.y + size1.y / 2.f - size2.y / 2.f :
              (vertical == AlignmentType::Vertical_Bottom ? pos.y + static_cast<float>(size1.y - size2.y) : 0.f);

    return newPos;
}

sf::Vector2f GUI::getAlignmentCoordinates(float x, float y, uint32_t width1, uint32_t height1, uint32_t width2, uint32_t height2, 
                                          AlignmentType horizontalAligment, AlignmentType verticalAligment)
{
    sf::Vector2f newPos;

    newPos.x = horizontalAligment == AlignmentType::Horizontal_Center ? x + width1 / 2.f - width2 / 2.f :
              (horizontalAligment == AlignmentType::Horizontal_Right ? x + static_cast<float>(width1 - width2) : 0.f);

    newPos.y = verticalAligment == AlignmentType::Vertical_Center ? y + height1 / 2.f - height2 / 2.f :
              (verticalAligment == AlignmentType::Vertical_Bottom ? y + static_cast<float>(height1 - height2) : 0.f);

    return newPos;
}

sf::Vector2f GUI::getAlignmentCoordinates(const sf::Vector2f& pos, const sf::Vector2u& size1, const sf::Vector2u& size2, 
                                          AlignmentType horizontalAligment, AlignmentType verticalAligment)
{
    sf::Vector2f newPos;

    newPos.x = horizontalAligment == AlignmentType::Horizontal_Center ? pos.x + size1.x / 2.f - size2.x / 2.f :
              (horizontalAligment == AlignmentType::Horizontal_Right ? pos.x + static_cast<float>(size1.x - size2.x) : 0.f);

    newPos.y = verticalAligment == AlignmentType::Vertical_Center ? pos.y + size1.y / 2.f - size2.y / 2.f :
              (verticalAligment == AlignmentType::Vertical_Bottom ? pos.y + static_cast<float>(size1.y - size2.y) : 0.f);

    return newPos;
}

//Margin

sf::Vector2f GUI::Margin::getCoordinates(float x, float y, AlignmentType horizontalAligment, AlignmentType verticalAligment)
{
    sf::Vector2f newPos;

    newPos.x = horizontalAligment == AlignmentType::Horizontal_Right ?
                    (x - horizontal) :
                    (x + horizontal);

    newPos.y = verticalAligment == AlignmentType::Vertical_Bottom ?
                    (y - vertical) :
                    (y + vertical);

    return newPos;
}

sf::Vector2f GUI::Margin::getCoordinates(const sf::Vector2f& pos, AlignmentType horizontalAligment, AlignmentType verticalAligment)
{
    sf::Vector2f newPos;

    newPos.x = horizontalAligment == AlignmentType::Horizontal_Right ?
                    (pos.x - horizontal) :
                    (pos.x + horizontal);

    newPos.y = verticalAligment == AlignmentType::Vertical_Bottom ?
                    (pos.y - vertical) :
                    (pos.y + vertical);

    return newPos;
}

sf::Vector2f GUI::getMarginCoordinates(float x, float y, AlignmentType horizontalAligment, AlignmentType verticalAligment, 
                                       uint32_t horizontalMargin, uint32_t verticalMargin)
{
    sf::Vector2f newPos;

    newPos.x = horizontalAligment == AlignmentType::Horizontal_Right ?
                    (x - horizontalMargin) :
                    (x + horizontalMargin);

    newPos.y = verticalAligment == AlignmentType::Vertical_Bottom ?
                    (y - verticalMargin) :
                    (y + verticalMargin);

    return newPos;
}

sf::Vector2f GUI::getMarginCoordinates(const sf::Vector2f& pos, AlignmentType horizontalAligment, AlignmentType verticalAligment, 
                                       uint32_t horizontalMargin, uint32_t verticalMargin)
{
    sf::Vector2f newPos;

    newPos.x = horizontalAligment == AlignmentType::Horizontal_Right ?
                    (pos.x - horizontalMargin) :
                    (pos.x + horizontalMargin);

    newPos.y = verticalAligment == AlignmentType::Vertical_Bottom ?
                    (pos.y - verticalMargin) :
                    (pos.y + verticalMargin);

    return newPos;
}

//Fitting

sf::FloatRect GUI::Fitting::getObjectRect(float x1, float y1, uint32_t width1, uint32_t height1, 
                                          float x2, float y2, uint32_t width2, uint32_t height2)
{
    sf::FloatRect newRectObject;

    newRectObject.left = horizontal ? x1 : x2;
    newRectObject.left = vertical ? y1 : y2;

    newRectObject.width = horizontal ? (width1 - horizontalOffset) : width2;
    newRectObject.height = vertical ? (height1 - verticalOffset) : height2;

    return newRectObject;
}

sf::FloatRect GUI::getFittingObjectRect(float x1, float y1, uint32_t width1, uint32_t height1, 
                                        float x2, float y2, uint32_t width2, uint32_t height2,
                                        bool horizontalFitting, bool verticalFitting,
                                        uint32_t horizontalFittingOffset, uint32_t verticalFittingOffset)
{
    sf::FloatRect newRectObject;

    newRectObject.left = horizontalFitting ? x1 : x2;
    newRectObject.left = verticalFitting ? y1 : y2;

    newRectObject.width = horizontalFitting ? (width1 - horizontalFittingOffset) : width2;
    newRectObject.height = verticalFitting ? (height1 - verticalFittingOffset) : height2;

    return newRectObject;
}

//Color Transition

sf::Color GUI::getColorTransition(const sf::Color& color1, const sf::Color& color2, float position)
{
    if (position < 0.f || position > 1.f)
        throw Error("ToolKit::getColorTransition: Position in Color Transition cannot be less than 0.0 or more than 1.0");

    return sf::Color(
		color1.r + static_cast<sf::Uint8>((color2.r - color1.r) * position),
		color1.g + static_cast<sf::Uint8>((color2.g - color1.g) * position),
		color1.b + static_cast<sf::Uint8>((color2.b - color1.b) * position),
		color1.a + static_cast<sf::Uint8>((color2.a - color1.a) * position)
	);
}