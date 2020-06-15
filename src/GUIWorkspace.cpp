#include "GUIWorkspace.hpp"

//Закрытые методы
void GUI::Workspace::setBorder(bool onBorder) {}

//Конструктор/Деструктор

GUI::Workspace::Workspace(sf::RenderTarget& target) 
    : Container(sf::Vector2f(0.f, 0.f), target.getSize()), clock(new sf::Clock)
{
    this->target = &target;

    border = new sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(size.x), static_cast<float>(size.y)));
    Transformable::setPosition(0.f, 0.f);
    updatedBorder = true;

    resize = true;
}

GUI::Workspace::Workspace(sf::RenderTarget& target, const sf::Vector2f& pos, const sf::Vector2u& size)
    : Container(pos, size), clock(new sf::Clock)
{
    this->target = &target;

    border = new sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(size.x), static_cast<float>(size.y)));
    Transformable::setPosition(0.f, 0.f);
    updatedBorder = true;
}

GUI::Workspace::Workspace(sf::RenderTarget& target, float x, float y, uint32_t width, uint32_t height)
    : Container(x, y, width, height), clock(new sf::Clock)
{
    this->target = &target;

    border = new sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(size.x), static_cast<float>(size.y)));
    Transformable::setPosition(0.f, 0.f);
    updatedBorder = true;
}

GUI::Workspace::~Workspace()
{
    delete clock;
}

//Методы

void GUI::Workspace::handleInput()
{
    if (!disabled)
        for (uint32_t i = childrens->size(); i > 0U; i--)
            (*childrens)[i - 1U]->handleIn();
}

void GUI::Workspace::handleEvent(const sf::Event& event)
{
    updatedBorder = event.type == sf::Event::Resized ? true : updatedBorder;

    if (resize && event.type == sf::Event::Resized) {
        setSize(
            static_cast<uint32_t>(event.size.width / static_cast<float>(sizeTarget.x)* static_cast<float>(size.x)),
            static_cast<uint32_t>(event.size.height / static_cast<float>(sizeTarget.y)* static_cast<float>(size.y))
        );

        sizeTarget = target->getSize();
    }
	if (reposition && event.type == sf::Event::Resized) {
        setPosition(
            static_cast<uint32_t>(event.size.width / static_cast<float>(sizeTarget.x) * localPos.x),
            static_cast<uint32_t>(event.size.height / static_cast<float>(sizeTarget.y) * localPos.y)
        );

        sizeTarget = target->getSize();
    }

    if (!disabled) {
        bool isScreenEventObject = false;
        Object* child;
        for (uint32_t i = childrens->size(); i > 0U; i--) {
            child = (*childrens)[i - 1U];

            if (!isScreenEventObject &&
                ((event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) &&
                    child->isPoint(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)) ||
                (event.type == sf::Event::MouseMoved &&
                    child->isPoint(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))))
            {
                child->handleEv(event);
                isScreenEventObject = true;
            } else
                child->handleEv(event);
        }
    }
}

void GUI::Workspace::update()
{
    float dt = clock->restart().asSeconds();

    if (updatedBorder)
        updateBorder();

    if (!disabled)
        for (auto& child : *childrens)
            child->upd(dt);
}

void GUI::Workspace::update(float dt)
{
    if (updatedBorder)
        updateBorder();
    
    if (!disabled)
        for (auto& child : *childrens)
            child->upd(dt);
}

void GUI::Workspace::render()
{
    if (!hidden) {
        const sf::View& prevView = target->getView();
        target->setView(*border);

        sf::RenderStates states(getTransform());

        for (auto& child : *childrens)
            drawObject(child, *target, states);

        target->setView(prevView);
    }
}