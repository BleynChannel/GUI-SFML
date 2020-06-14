#include "GUIBaseButton.hpp"
#include "GUIError.hpp"

//Закрытые методы

void GUI::BaseButton::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Button::Left &&
        isPoint(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) 
    {
        pressed = !pressed;

        Animation* tmpAnimation = (*animations)[0];
        if (animatedPressed && tmpAnimation) {
            tmpAnimation->stop();

            tmpAnimation->start(animationPressedDuration);
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

                tmpAnimation->start(tmpPosition * animationPressedDuration);
            }

            if (onTouch)
                onTouch(this, event.mouseButton.x, event.mouseButton.y);
        } else {
            pressed = !pressed;

            if (animatedPressed && tmpAnimation) {
                float tmpPosition = tmpAnimation->position;
                tmpAnimation->stop();

                tmpAnimation->start(tmpPosition * animationPressedDuration);
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

                tmpAnimation = (*animations)[1];
                if (animatedHover && tmpAnimation) {
                    tmpAnimation->stop();

                    tmpAnimation->start(animationPressedDuration);
                }
            } else if (hover && !mouseInButton) {
                hover = false;

                tmpAnimation = (*animations)[1];
                if (animatedHover && tmpAnimation) {
                    float tmpPosition = tmpAnimation->position;
                    tmpAnimation->stop();

                    tmpAnimation->start(tmpPosition * animationPressedDuration);
                }
            }
        }
    }
}

void GUI::BaseButton::render(sf::RenderTarget& target, sf::RenderStates states) const
{
    drawObject(panel, target, states);
    drawObject(text, target, states);
}

//Кастомные методы
void GUI::BaseButton::customSetSize(const sf::Vector2u& size)
{
    this->size = size;

    uint32_t maxSize = text->getSize().y + marginText * 2U;
    this->size.y = size.y < maxSize ? maxSize : size.y;
}

void GUI::BaseButton::customSetSize(uint32_t width, uint32_t height)
{
    size = sf::Vector2u(width, height);

    uint32_t maxSize = text->getSize().y + marginText * 2U;
    size.y = height < maxSize ? maxSize : height;
}

//Кастомное обновление трансформации

void GUI::BaseButton::customUpdateTransform()
{
    panel->setSize(size);

    uint32_t i = 0U;
    do
        text->setString(string.substring(0U, string.getSize() - i++));
    while (text->getSize().x > size.x - marginText * 2);

    const auto& sizeText = text->getSize();
    text->setOrigin(sizeText.x / 2.f, sizeText.y / 2.f);

    text->setPosition(size.x / 2.f, size.y / 2.f);
}

//Конструкторы

GUI::BaseButton::BaseButton(sf::String text, const sf::Font* font)
    : Object(), panel(new Panel(0.f, 0.f, 0U, 0U, sf::Color::White)), text(new CuttedText(text, font, sf::Color::Black)),
      isMousePressed(false), marginText(Application::getButtonMarginText()), onTouch(nullptr), 
      pressed(false), hover(false), switchMode(false), 
      hoverMode(Application::getButtonOnHoverMode()), string(text), 
      animationPressedDuration(Application::getButtonAnimationPressedDuration()), 
      animationHoverDuration(Application::getButtonAnimationHoverDuration())
{
    connectObject(this->panel);
    connectObject(this->text);

    customUpdateTransform();

    animations->resize(2);

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}

GUI::BaseButton::BaseButton(const sf::Vector2f& pos, const sf::Vector2u& size, sf::String text, const sf::Font* font)
    : Object(pos, size), panel(new Panel(0.f, 0.f, size.x, size.y, sf::Color::White)), 
      text(new CuttedText(text, font, sf::Color::Black)),
      isMousePressed(false), marginText(Application::getButtonMarginText()), onTouch(nullptr),
      pressed(false), hover(false), switchMode(false),
      hoverMode(Application::getButtonOnHoverMode()), string(text),
      animationPressedDuration(Application::getButtonAnimationPressedDuration()),
      animationHoverDuration(Application::getButtonAnimationHoverDuration())
{
    connectObject(this->panel);
    connectObject(this->text);

    customUpdateTransform();

    animations->resize(2);

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}

GUI::BaseButton::BaseButton(float x, float y, uint32_t width, uint32_t height, sf::String text, const sf::Font* font)
    : Object(x, y, width, height), panel(new Panel(0.f, 0.f, width, height, sf::Color::White)), 
      text(new CuttedText(text, font, sf::Color::Black)),
      isMousePressed(false), marginText(Application::getButtonMarginText()), onTouch(nullptr),
      pressed(false), hover(false), switchMode(false),
      hoverMode(Application::getButtonOnHoverMode()), string(text),
      animationPressedDuration(Application::getButtonAnimationPressedDuration()),
      animationHoverDuration(Application::getButtonAnimationHoverDuration())
{
    connectObject(this->panel);
    connectObject(this->text);

    customUpdateTransform();

    animations->resize(2);

    setAnimatedPressed(Application::getButtonOnAnimationPressed());
    setAnimatedHover(Application::getButtonOnAnimationHover());
}


//Геттеры

const std::function<void(GUI::BaseButton*, int, int)>& GUI::BaseButton::getOnTouch() const
{
    return onTouch;
}

bool GUI::BaseButton::getPressed() const
{
    return pressed;
}

bool GUI::BaseButton::getHover() const
{
    return hover;
}

bool GUI::BaseButton::getSwitchMode() const
{
    return switchMode;
}

bool GUI::BaseButton::getHoverMode() const
{
    return hoverMode;
}

uint32_t GUI::BaseButton::getMarginText() const
{
    return marginText;
}

bool GUI::BaseButton::getAnimatedPressed() const
{
    return animatedPressed;
}

float GUI::BaseButton::getAnimationPressedDuration() const
{
    return animationPressedDuration;
}

bool GUI::BaseButton::getAnimatedHover() const
{
    return animatedHover;
}

float GUI::BaseButton::getAnimationHoverDuration() const
{
    return animationHoverDuration;
}

//Сеттеры

void GUI::BaseButton::setOnTouch(const std::function<void(BaseButton*, int, int)>& onTouch)
{
    this->onTouch = onTouch;
}

void GUI::BaseButton::setSwitchMode(bool switchMode)
{
    this->switchMode = switchMode;
}

void GUI::BaseButton::setHoverMode(bool hoverMode)
{
    this->hoverMode = hoverMode;
}

void GUI::BaseButton::setMarginText(uint32_t marginText)
{
    this->marginText = marginText;
}

void GUI::BaseButton::setAnimatedPressed(bool animated)
{
    animatedPressed = animated;
}

void GUI::BaseButton::setAnimationPressedDuration(float duration)
{
    animationPressedDuration = duration;
}

void GUI::BaseButton::setAnimatedHover(bool animated)
{
    animatedHover = animated;
}

void GUI::BaseButton::setAnimationHoverDuration(float duration)
{
    animationHoverDuration = duration;
}

//Методы

void GUI::BaseButton::createAnimation(const std::function<void(const Animation&)> frameHandle, 
                                      const std::function<void()>& onFinish)
{
    if ((*animations)[0])
        (*animations)[1] = new Animation(frameHandle, onFinish);
    else
        (*animations)[0] = new Animation(frameHandle, onFinish);
}

void GUI::BaseButton::changeAnimation(uint32_t index, const std::function<void(const Animation&)> frameHandle, 
                                      const std::function<void()>& onFinish)
{
    if (index < 2U) {
        delete (*animations)[index];
        (*animations)[index] = new Animation(frameHandle, onFinish);
    } else
        throw Error("Object::changeAnimation: Index more than the number of animations");
}

void GUI::BaseButton::removeAnimation(uint32_t index)
{
    if (index < 2U) {
        delete (*animations)[index];
        (*animations)[index] = nullptr;
    } else
        throw Error("Object::removeAnimation: Index more than the number of animations");
}