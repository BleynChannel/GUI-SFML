#include "GUIContainer.hpp"
#include "GUIError.hpp"

//Закрытые методы

void GUI::Container::updateIndex(uint32_t fromIndex)
{
    size_t size = childrens->size();
    for (uint32_t i = fromIndex; i < size; i++)
        (*childrens)[i]->index = i;
}

void GUI::Container::updateFirstParent(Container* newFirstParent)
{
    firstParent = newFirstParent;

    for (auto& child : *childrens)
        child->updateFirstParent(newFirstParent);
}

void GUI::Container::setTarget(sf::RenderTarget* target)
{
    if (!this->target && target) {
        this->target = target;
        updatedBorder = true;

        for (auto& connect : *connects)
            connect->setTarget(target);

        for (auto& child : *childrens)
            child->setTarget(target);

        sizeTarget = target->getSize();
    }
}

void GUI::Container::handleIn()
{
    if (!disabled)
        handleInput();

    size_t sizeConnects = connects->size();
    for (uint32_t i = sizeConnects; i > 0U; i--)
        (*connects)[i - 1U]->handleIn();

    size_t size = childrens->size();
    for (uint32_t i = size; i > 0U; i--)
        (*childrens)[i - 1U]->handleIn();
}

void GUI::Container::handleEv(const sf::Event& event)
{
    updatedBorder = event.type == sf::Event::Resized ? true : updatedBorder;

    if (resize && event.type == sf::Event::Resized) {
        setSize(
            static_cast<uint32_t>(event.size.width / static_cast<float>(sizeTarget.x) * static_cast<float>(size.x)),
            static_cast<uint32_t>(event.size.height / static_cast<float>(sizeTarget.y) * static_cast<float>(size.y))
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

    if (!disabled)
        handleEvent(event);

    bool isScreenEventObject = false;

    Object* connect;
    for (uint32_t i = connects->size(); i > 0U; i--) {
        connect = (*connects)[i - 1U];

        if (!isScreenEventObject &&
            ((event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) &&
                connect->isPoint(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)) ||
             (event.type == sf::Event::MouseMoved &&
                connect->isPoint(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))))
        {
            connect->handleEv(event);
            isScreenEventObject = true;
        } else
            connect->handleEv(event);
    }

    isScreenEventObject = false;

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

void GUI::Container::upd(float dt)
{
    if (border && updatedBorder)
        updateBorder();

    if (!disabled)
        update(dt);

    for (auto& connect : *connects)
        connect->upd(dt);

    for (auto& child : *childrens)
        child->upd(dt);

    if (!disabled && !hidden) {
        for (auto& animation : *animations)
            if (animation)
                if (animation->started)
                {
                    animation->currentTime += dt;
                    animation->position = (animation->currentTime - animation->startTime) / animation->duration;

                    if (animation->position < 1.f)
                        animation->frameHandle(*animation);
                    else {
                        animation->position = 1.f;
                        animation->started = false;

                        animation->frameHandle(*animation);

                        if (animation->onFinish)
                            animation->onFinish();
                    }
                }
    }
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if (!hidden)
        render(target, states);

    for (auto& child : *childrens)
        drawObject(child, target, states);
}

//Конструктор/Деструктор

GUI::Container::Container() : childrens(new std::vector<Object*>) {}

GUI::Container::Container(const sf::Vector2f& pos, const sf::Vector2u& size)
    : Object(pos, size), childrens(new std::vector<Object*>) {}

GUI::Container::Container(float x, float y, uint32_t width, uint32_t height)
    : Object(x, y, width, height), childrens(new std::vector<Object*>) {}

GUI::Container::~Container()
{
    while (!childrens->empty())
        (*childrens)[0]->remove();

    delete childrens;
}

//Методы

GUI::Object* GUI::Container::addChild(Object* obj)
{
    if (obj) {
        obj->remove();

        childrens->push_back(obj);
        obj->parent = this;
        obj->updateFirstParent(firstParent ? firstParent : this);
        obj->index = childrens->size() - 1U;

        obj->setTarget(target);

        obj->setPosition(obj->localPos);
    }

    return obj;
}

GUI::Object* GUI::Container::addChild(Object* obj, uint32_t index)
{
    if (obj)
        if (index < childrens->size()) {
            obj->remove();

            childrens->insert(childrens->begin() + index, obj);
            obj->parent = this;
            obj->updateFirstParent(firstParent ? firstParent : this);
            
            updateIndex(index);
            obj->setTarget(target);

            obj->setPosition(obj->localPos);
        } else
            throw Error("Container::addChild: Index more than the number of childrens");

    return obj;
}

void GUI::Container::removeChildren(uint32_t index)
{
    if (index < childrens->size())
        (*childrens)[index]->remove();
    else
        throw Error("Container::removeChildren: Index more than the number of childrens");
}

void GUI::Container::removeChildrens(uint32_t fromIndex)
{
    size_t size = childrens->size();
    for (uint32_t i = fromIndex; i < size; i++)
        (*childrens)[i]->remove();
}

void GUI::Container::removeChildrens(uint32_t fromIndex, uint32_t toIndex)
{
    toIndex = toIndex < childrens->size() ? toIndex : (childrens->size() - 1U);

	for (uint32_t i = fromIndex; i <= toIndex; i++)
        (*childrens)[i]->remove();
}

GUI::Object* GUI::Container::getChildren(uint32_t index)
{
    if (index < childrens->size())
        return (*childrens)[index];
    
    throw Error("Container::getChildren: Index more than the number of childrens");
}

std::vector<GUI::Object*>& GUI::Container::getChildrens()
{
    return *childrens;
}

//Object

void GUI::Container::setPosition(const sf::Vector2f& pos)
{
    customSetPosition(pos);

    if (parent)
        this->pos = parent->pos - parent->origin + localPos;
    else if (connect)
        this->pos = connect->pos - connect->origin + localPos;
    else
        this->pos = localPos;

    if (border) {
        Transformable::setPosition(0.f, 0.f);
        updatedBorder = true;
    } else
        Transformable::setPosition(localPos);

    for (auto& connect : *connects)
        connect->setPosition(connect->localPos);

    for (auto& child : *childrens)
        child->setPosition(child->localPos);

    customUpdateTransform();
}

void GUI::Container::setPosition(float x, float y)
{
    customSetPosition(x, y);

    if (parent)
        this->pos = parent->pos - parent->origin + localPos;
    else if (connect)
        this->pos = connect->pos - connect->origin + localPos;
    else
        this->pos = localPos;

    if (border) {
        Transformable::setPosition(0.f, 0.f);
        updatedBorder = true;
    } else
        Transformable::setPosition(localPos);

    for (auto& connect : *connects)
        connect->setPosition(connect->localPos);

    for (auto& child : *childrens)
        child->setPosition(child->localPos);

    customUpdateTransform();
}

void GUI::Container::setSize(const sf::Vector2u& size)
{
    sf::Vector2u oldSize = this->size;
    customSetSize(size);

    setOrigin(
        oldSize.x ? (size.x / static_cast<float>(oldSize.x)* origin.x) : 0.f,
        oldSize.y ? (size.y / static_cast<float>(oldSize.y)* origin.y) : 0.f
    );

    updatedBorder = true;

    for (auto& connect : *connects)
        connect->updatedBorder = true;

    for (auto& child : *childrens)
        child->updatedBorder = true;

    customUpdateTransform();
}

void GUI::Container::setSize(uint32_t width, uint32_t height)
{
    sf::Vector2u oldSize = size;
    customSetSize(width, height);

    setOrigin(
        oldSize.x ? (size.x / static_cast<float>(oldSize.x) * origin.x) : 0.f,
        oldSize.y ? (size.y / static_cast<float>(oldSize.y) * origin.y) : 0.f
    );

    updatedBorder = true;

    for (auto& connect : *connects)
        connect->updatedBorder = true;

    for (auto& child : *childrens)
        child->updatedBorder = true;

    customUpdateTransform();
}