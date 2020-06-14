#include "GUIButton.hpp"

//Закрытые методы

void GUI::Button::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Button::Left &&
        isPoint(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) 
    {
        pressed = !pressed;

        Animation* tmpAnimation = (*animations)[0];
        if (animatedPressed && tmpAnimation) {
            tmpAnimation->stop();

            currentBackgroundColor = &panel->getColor();
            currentTextColor = &text->getColor();

            tmpAnimation->start(animationPressedDuration);
        } else if (pressed) {
            currentBackgroundColor = &panel->getColor();
            currentTextColor = &text->getColor();

            panel->setColor(backgroundPressedColor ? *backgroundPressedColor : *currentBackgroundColor);
            text->setColor(textPressedColor ? *textPressedColor : *currentTextColor);
        } else {
            panel->setColor(*backgroundColor);
            text->setColor(*textColor);
        }

        isMousePressed = true;
    } else if (isMousePressed &&
               event.type == sf::Event::MouseButtonReleased &&
               event.mouseButton.button == sf::Mouse::Button::Left)
    {
        Animation* tmpAnimation = (*animations)[0];

        if (isPoint(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
            pressed = switchMode ? pressed : false;

            if (animatedPressed && tmpAnimation) {
                float tmpPosition = tmpAnimation->position;
                tmpAnimation->stop();

                currentBackgroundColor = &panel->getColor();
                currentTextColor = &text->getColor();

                tmpAnimation->start(tmpPosition * animationPressedDuration);
            } else if (pressed) {
                currentBackgroundColor = &panel->getColor();
                currentTextColor = &text->getColor();

                panel->setColor(backgroundPressedColor ? *backgroundPressedColor : *currentBackgroundColor);
                text->setColor(textPressedColor ? *textPressedColor : *currentTextColor);
            } else {
                panel->setColor(*backgroundColor);
                text->setColor(*textColor);
            }

            if (onTouch)
                onTouch(this, event.mouseButton.x, event.mouseButton.y);
        } else {
            pressed = !pressed;

            if (animatedPressed && tmpAnimation) {
                float tmpPosition = tmpAnimation->position;
                tmpAnimation->stop();

                currentBackgroundColor = &panel->getColor();
                currentTextColor = &text->getColor();

                tmpAnimation->start(tmpPosition * animationPressedDuration);
            } else if (pressed) {
                currentBackgroundColor = &panel->getColor();
                currentTextColor = &text->getColor();

                panel->setColor(backgroundPressedColor ? *backgroundPressedColor : *currentBackgroundColor);
                text->setColor(textPressedColor ? *textPressedColor : *currentTextColor);
            } else {
                panel->setColor(*backgroundColor);
                text->setColor(*textColor);
            }
        }

        isMousePressed = false;
    } else if (hoverMode && !isMousePressed && event.type == sf::Event::MouseMoved) {
        Animation* tmpAnimation = (*animations)[0];
        bool stateAnimationPressed = false;
        if (tmpAnimation)
            stateAnimationPressed = tmpAnimation->started;
        else
            stateAnimationPressed = false;

        if (!stateAnimationPressed) {
            bool mouseInButton = isPoint(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));

            if (!hover && mouseInButton) {
                hover = true;

                currentBackgroundColor = &panel->getColor();
                currentTextColor = &text->getColor();

                tmpAnimation = (*animations)[1];
                if (animatedHover && tmpAnimation) {
                    tmpAnimation->stop();
                    tmpAnimation->start(animationHoverDuration);
                } else if (pressed) {
                    panel->setColor(backgroundHoverPressedColor ? *backgroundHoverPressedColor : *currentBackgroundColor);
                    text->setColor(textHoverPressedColor ? *textHoverPressedColor : *currentTextColor);
                } else {
                    panel->setColor(backgroundHoverColor ? *backgroundHoverColor : *currentBackgroundColor);
                    text->setColor(textHoverColor ? *textHoverColor : *currentTextColor);
                }
            } else if (hover && !mouseInButton) {
                hover = false;

                tmpAnimation = (*animations)[1];
                if (animatedHover && tmpAnimation) {
                    float tmpPosition = tmpAnimation->position;
                    tmpAnimation->stop();

                    currentBackgroundColor = &panel->getColor();
                    currentTextColor = &text->getColor();

                    tmpAnimation->start(tmpPosition * animationHoverDuration);
                } else if (pressed) {
                    currentBackgroundColor = &panel->getColor();
                    currentTextColor = &text->getColor();

                    panel->setColor(backgroundPressedColor ? *backgroundPressedColor : *currentBackgroundColor);
                    text->setColor(textPressedColor ? *textPressedColor : *currentTextColor);
                } else {
                    panel->setColor(*backgroundColor);
                    text->setColor(*textColor);
                }
            }
        }
    }
}

//Конструкторы

GUI::Button::Button(const sf::Color& backgroundColor, const sf::Color& textColor, 
                    sf::String text, const sf::Font* font)
    : BaseButton(text, font),
      backgroundColor(new sf::Color(backgroundColor)), textColor(new sf::Color(textColor)),
      backgroundPressedColor(nullptr), textPressedColor(nullptr),
      backgroundHoverColor(nullptr), textHoverColor(nullptr),
      backgroundHoverPressedColor(nullptr), textHoverPressedColor(nullptr),
      backgroundDisabledColor(new sf::Color(0x878787FF)), textDisabledColor(new sf::Color(0xA5A5A5FF))
{
    panel->setColor(backgroundColor);
    this->text->setColor(textColor);

    currentBackgroundColor = this->backgroundColor;
    currentTextColor = this->textColor;

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}

GUI::Button::Button(const sf::Color& backgroundColor, const sf::Color& textColor, 
                    const sf::Color& backgroundDisabledColor, const sf::Color& textDisabledColor, 
                    sf::String text, const sf::Font* font)
    : BaseButton(text, font),
      backgroundColor(new sf::Color(backgroundColor)), textColor(new sf::Color(textColor)),
      backgroundPressedColor(nullptr), textPressedColor(nullptr),
      backgroundHoverColor(nullptr), textHoverColor(nullptr),
      backgroundHoverPressedColor(nullptr), textHoverPressedColor(nullptr),
      backgroundDisabledColor(new sf::Color(backgroundDisabledColor)), textDisabledColor(new sf::Color(textDisabledColor))
{
    panel->setColor(backgroundColor);
    this->text->setColor(textColor);

    currentBackgroundColor = this->backgroundColor;
    currentTextColor = this->textColor;

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}

GUI::Button::Button(const sf::Vector2f& pos, const sf::Vector2u& size,
                    const sf::Color& backgroundColor, const sf::Color& textColor, 
                    sf::String text, const sf::Font* font)
    : BaseButton(pos, size, text, font),
      backgroundColor(new sf::Color(backgroundColor)), textColor(new sf::Color(textColor)),
      backgroundPressedColor(nullptr), textPressedColor(nullptr),
      backgroundHoverColor(nullptr), textHoverColor(nullptr),
      backgroundHoverPressedColor(nullptr), textHoverPressedColor(nullptr),
      backgroundDisabledColor(new sf::Color(0x878787FF)), textDisabledColor(new sf::Color(0xA5A5A5FF))
{
    panel->setColor(backgroundColor);
    this->text->setColor(textColor);

    currentBackgroundColor = this->backgroundColor;
    currentTextColor = this->textColor;

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}

GUI::Button::Button(const sf::Vector2f& pos, const sf::Vector2u& size,
                    const sf::Color& backgroundColor, const sf::Color& textColor, 
                    const sf::Color& backgroundDisabledColor, const sf::Color& textDisabledColor, 
                    sf::String text, const sf::Font* font)
    : BaseButton(pos, size, text, font),
      backgroundColor(new sf::Color(backgroundColor)), textColor(new sf::Color(textColor)),
      backgroundPressedColor(nullptr), textPressedColor(nullptr),
      backgroundHoverColor(nullptr), textHoverColor(nullptr),
      backgroundHoverPressedColor(nullptr), textHoverPressedColor(nullptr),
      backgroundDisabledColor(new sf::Color(backgroundDisabledColor)), textDisabledColor(new sf::Color(textDisabledColor))
{
    panel->setColor(backgroundColor);
    this->text->setColor(textColor);

    currentBackgroundColor = this->backgroundColor;
    currentTextColor = this->textColor;

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}

GUI::Button::Button(float x, float y, uint32_t width, uint32_t height,
                    const sf::Color& backgroundColor, const sf::Color& textColor, 
                    sf::String text, const sf::Font* font)
    : BaseButton(x, y, width, height, text, font),
      backgroundColor(new sf::Color(backgroundColor)), textColor(new sf::Color(textColor)),
      backgroundPressedColor(nullptr), textPressedColor(nullptr),
      backgroundHoverColor(nullptr), textHoverColor(nullptr),
      backgroundHoverPressedColor(nullptr), textHoverPressedColor(nullptr),
      backgroundDisabledColor(new sf::Color(0x878787FF)), textDisabledColor(new sf::Color(0xA5A5A5FF))
{
    panel->setColor(backgroundColor);
    this->text->setColor(textColor);

    currentBackgroundColor = this->backgroundColor;
    currentTextColor = this->textColor;

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}

GUI::Button::Button(float x, float y, uint32_t width, uint32_t height,
                    const sf::Color& backgroundColor, const sf::Color& textColor, 
                    const sf::Color& backgroundDisabledColor, const sf::Color& textDisabledColor, 
                    sf::String text, const sf::Font* font)
    : BaseButton(x, y, width, height, text, font),
      backgroundColor(new sf::Color(backgroundColor)), textColor(new sf::Color(textColor)),
      backgroundPressedColor(nullptr), textPressedColor(nullptr),
      backgroundHoverColor(nullptr), textHoverColor(nullptr),
      backgroundHoverPressedColor(nullptr), textHoverPressedColor(nullptr),
      backgroundDisabledColor(new sf::Color(backgroundDisabledColor)), textDisabledColor(new sf::Color(textDisabledColor))
{
    panel->setColor(backgroundColor);
    this->text->setColor(textColor);

    currentBackgroundColor = this->backgroundColor;
    currentTextColor = this->textColor;

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}

GUI::Button::~Button()
{
    delete backgroundColor;

    if (backgroundPressedColor)
        delete backgroundPressedColor;
    if (backgroundHoverColor)
        delete backgroundHoverColor;
    if (backgroundHoverPressedColor)
        delete backgroundHoverPressedColor;
    if (backgroundDisabledColor)
        delete backgroundDisabledColor;

    delete textColor;

    if (textPressedColor)
        delete textPressedColor;
    if (textHoverColor)
        delete textHoverColor;
    if (textHoverPressedColor)
        delete textHoverPressedColor;
    if (textDisabledColor)
        delete textDisabledColor;
}

//Геттеры

const sf::Color* GUI::Button::getBackgroundColor() const
{
    return backgroundColor;
}

const sf::Color* GUI::Button::getTextColor() const
{
    return textColor;
}

const sf::Color* GUI::Button::getBackgroundPressedColor() const
{
    return backgroundPressedColor;
}

const sf::Color* GUI::Button::getTextPressedColor() const
{
    return textPressedColor;
}

const sf::Color* GUI::Button::getBackgroundHoverColor() const
{
    return backgroundHoverColor;
}

const sf::Color* GUI::Button::getBackgroundHoverPressedColor() const
{
    return backgroundHoverPressedColor;
}

const sf::Color* GUI::Button::getTextHoverColor() const
{
    return textHoverColor;
}

const sf::Color* GUI::Button::getTextHoverPressedColor() const
{
    return textHoverPressedColor;
}

const sf::Color* GUI::Button::getBackgroundDisabledColor() const
{
    return backgroundDisabledColor;
}

const sf::Color* GUI::Button::getTextDisabledColor() const
{
    return textDisabledColor;
}

//Сеттеры

void GUI::Button::setAnimatedPressed(bool animated)
{
    animatedPressed = animated;

    if (animated && !(*animations)[0])
        createAnimation(
            [this](const Animation& anim) 
            {
                panel->setColor(getColorTransition(
                    *currentBackgroundColor, 
                    pressed ? 
                        *(backgroundPressedColor ? backgroundPressedColor : currentBackgroundColor) : 
                        *backgroundColor, 
                    anim.position
                ));
                text->setColor(getColorTransition(
                    *currentTextColor, 
                    pressed ? 
                        *(textPressedColor ? textPressedColor : currentTextColor) : 
                        *textColor, 
                    anim.position
                ));
            }
        );
}

void GUI::Button::setAnimatedHover(bool animated)
{
    animatedHover = animated;

    if (animated && !(*animations)[1])
        createAnimation(
            [this](const Animation& anim) 
            {
                panel->setColor(getColorTransition(
                    *currentBackgroundColor, 
                    hover ? 
                        (pressed ? 
                            *(backgroundHoverPressedColor ? backgroundHoverPressedColor : currentBackgroundColor) : 
                            *(backgroundHoverColor ? backgroundHoverColor : currentBackgroundColor)) : 
                        (pressed ? 
                            *(backgroundPressedColor ? backgroundPressedColor : currentBackgroundColor) : 
                            *(backgroundColor ? backgroundColor : currentBackgroundColor)), 
                    anim.position
                ));
                text->setColor(getColorTransition(
                    *currentTextColor, 
                    hover ? 
                        (pressed ? 
                            *(textHoverPressedColor ? textHoverPressedColor : currentTextColor) : 
                            *(textHoverColor ? textHoverColor : currentTextColor)) : 
                        (pressed ? 
                            *(textPressedColor ? textPressedColor : currentTextColor) : 
                            *(textColor ? textColor : currentTextColor)), 
                    anim.position
                ));
            }
        );
}

void GUI::Button::setBackgroundColor(const sf::Color& color)
{
    *backgroundColor = color;
}

void GUI::Button::setTextColor(const sf::Color& color)
{
    *textColor = color;
}

void GUI::Button::setBackgroundPressedColor(const sf::Color& color)
{
    if (backgroundPressedColor)
        *backgroundPressedColor = color;
    else
        backgroundPressedColor = new sf::Color(color);
}

void GUI::Button::setTextPressedColor(const sf::Color& color)
{
    if (textPressedColor)
        *textPressedColor = color;
    else
        textPressedColor = new sf::Color(color);
}

void GUI::Button::setBackgroundHoverColor(const sf::Color& color)
{
    if (backgroundHoverColor)
        *backgroundHoverColor = color;
    else
        backgroundHoverColor = new sf::Color(color);
}

void GUI::Button::setBackgroundHoverPressedColor(const sf::Color& color)
{
    if (backgroundHoverPressedColor)
        *backgroundHoverPressedColor = color;
    else
        backgroundHoverPressedColor = new sf::Color(color);
}

void GUI::Button::setTextHoverColor(const sf::Color& color)
{
    if (textHoverColor)
        *textHoverColor = color;
    else
        textHoverColor = new sf::Color(color);
}

void GUI::Button::setTextHoverPressedColor(const sf::Color& color)
{
    if (textHoverPressedColor)
        *textHoverPressedColor = color;
    else
        textHoverPressedColor = new sf::Color(color);
}

void GUI::Button::setBackgroundDisabledColor(const sf::Color& color)
{
    *backgroundDisabledColor = color;
}

void GUI::Button::setTextDisabledColor(const sf::Color& color)
{
    *textDisabledColor = color;
}

void GUI::Button::setDisabled(bool disabled)
{
    this->disabled = disabled;

    if (disabled) {
        panel->setColor(*backgroundDisabledColor);
        text->setColor(*textDisabledColor);
    } else {
        panel->setColor(*currentBackgroundColor);
        text->setColor(*currentTextColor);
    }
}

//Text

//Геттеры

const sf::String& GUI::Button::getTextString() const
{
    return string;
}

const sf::Font* GUI::Button::getTextFont() const
{
    return text->getFont();
}

size_t GUI::Button::getTextCharacterSize() const
{
    return text->getCharacterSize();
}

float GUI::Button::getTextLetterSpacing() const
{
    return text->getLetterSpacing();
}

float GUI::Button::getTextLineSpacing() const
{
    return text->getLineSpacing();
}

sf::Uint32 GUI::Button::getTextStyle() const
{
    return text->getStyle();
}

const sf::Color& GUI::Button::getTextOutlineColor() const
{
    return text->getOutlineColor();
}

float GUI::Button::getTextOutlineThickness() const
{
    return text->getOutlineThickness();
}

//Сеттеры

void GUI::Button::setTextString(const sf::String& string)
{
    this->string = string;
    text->setString(string);

    customUpdateTransform();
}

void GUI::Button::setTextFont(const sf::Font& font)
{
    text->setFont(font);
    customUpdateTransform();
}

void GUI::Button::setTextCharacterSize(size_t size)
{
    text->setCharacterSize(size);
    customUpdateTransform();
}

void GUI::Button::setTextLineSpacing(float spacingFactor)
{
    text->setLineSpacing(spacingFactor);
}

void GUI::Button::setTextLetterSpacing(float spacingFactor)
{
    text->setLetterSpacing(spacingFactor);
    customUpdateTransform();
}

void GUI::Button::setTextStyle(sf::Uint32 style)
{
    text->setStyle(style);
    customUpdateTransform();
}

void GUI::Button::setTextOutlineColor(const sf::Color& color)
{
    text->setOutlineColor(color);
}

void GUI::Button::setTextOutlineThickness(float thickness)
{
    text->setOutlineThickness(thickness);
    customUpdateTransform();
}

void GUI::Button::setTextSize(const sf::Vector2u& size)
{
    if (size.x < this->size.x && size.y < this->size.y)
        text->setSize(size);

    customUpdateTransform();
}

void GUI::Button::setTextSize(uint32_t width, uint32_t height)
{
    if (width < size.x && height < size.y)
        text->setSize(width, height);

    customUpdateTransform();
}

void GUI::Button::setTextRotation(float angle)
{
    text->setRotation(angle);
}

//Методы

void GUI::Button::textScale(const sf::Vector2i& scaled)
{
    const sf::Vector2u& sizeText = text->getSize();
    if (sizeText.x + scaled.x < size.x && sizeText.y + scaled.y < size.y)
        text->scale(scaled);

    customUpdateTransform();
}

void GUI::Button::textScale(int scaledX, int scaledY)
{
    const sf::Vector2u& sizeText = text->getSize();
    if (sizeText.x + scaledX < size.x && sizeText.y + scaledY < size.y)
        text->scale(scaledX, scaledY);

    customUpdateTransform();
}

void GUI::Button::textRotate(float angle)
{
    text->rotate(angle);
}


//Методы

sf::Vector2f GUI::Button::findTextCharacterPos(sf::Uint32 index) const
{
    return text->findCharacterPos(index);
}