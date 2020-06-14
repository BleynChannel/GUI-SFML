#include "GUIObject.hpp"
#include "GUIContainer.hpp"
#include "GUIError.hpp"

//Закрытые методы

void GUI::Object::updateBorder()
{
    //Выстовляю границы барьера в зависимости от окна
    sf::View* tmpBorder = nullptr;
    const sf::FloatRect* rectTmpBorderViewport;
    sf::FloatRect rectTmpBorder;
    const sf::Vector2u* sizeTarget;

    if (target)
        sizeTarget = &target->getSize();
    else
        sizeTarget = nullptr;

    Object* tmpObject = parent ? parent : (connect ? connect : nullptr);

    if (tmpObject) {
        while (!tmpObject->border)
            tmpObject = tmpObject->parent ? tmpObject->parent : tmpObject->connect;
            
        tmpBorder = tmpObject->border;
    }

    if (sizeTarget) {
        if (parent) {
            rectTmpBorderViewport = &tmpBorder->getViewport();

            rectTmpBorder = sf::FloatRect(
                rectTmpBorderViewport->left * static_cast<float>(sizeTarget->x),
                rectTmpBorderViewport->top * static_cast<float>(sizeTarget->y),
                rectTmpBorderViewport->width * static_cast<float>(sizeTarget->x),
                rectTmpBorderViewport->height * static_cast<float>(sizeTarget->y)
            );
        }
        else if (connect) {
            rectTmpBorderViewport = &tmpBorder->getViewport();

            rectTmpBorder = sf::FloatRect(
                rectTmpBorderViewport->left * static_cast<float>(sizeTarget->x),
                rectTmpBorderViewport->top * static_cast<float>(sizeTarget->y),
                rectTmpBorderViewport->width * static_cast<float>(sizeTarget->x),
                rectTmpBorderViewport->height * static_cast<float>(sizeTarget->y)
            );
        }
        else if (target)
            rectTmpBorder = sf::FloatRect(
                0.f, 0.f, static_cast<float>(sizeTarget->x), static_cast<float>(sizeTarget->y)
            );

        rectBorder = sf::FloatRect(
            localPos.x - origin.x < 0.f ?
                rectTmpBorder.left :
                (localPos.x - origin.x > rectTmpBorder.width ?
                    (rectTmpBorder.left + rectTmpBorder.width) :
                    (pos.x - origin.x)),
            localPos.y - origin.y < 0.f ?
                rectTmpBorder.top :
                (localPos.y - origin.y > rectTmpBorder.height ?
                    (rectTmpBorder.top + rectTmpBorder.height) :
                    (pos.y - origin.y)),
            localPos.x - origin.x < 0.f ?
                (static_cast<float>(size.x) + localPos.x - origin.x < 0.f ?
                    0.f :
                    (static_cast<float>(size.x) + localPos.x - origin.x)) :
                (localPos.x - origin.x < rectTmpBorder.width ?
                    (localPos.x - origin.x + static_cast<float>(size.x) > rectTmpBorder.width ?
                        (rectTmpBorder.width - (localPos.x - origin.x)) :
                         static_cast<float>(size.x)) :
                    0.f),
            localPos.y - origin.y < 0.f ?
                (static_cast<float>(size.y) + localPos.y - origin.y < 0.f ?
                    0.f :
                    (static_cast<float>(size.y) + localPos.y - origin.y)) :
                (localPos.y - origin.y < rectTmpBorder.height ?
                    (localPos.y - origin.y + static_cast<float>(size.y) > rectTmpBorder.height ?
                        (rectTmpBorder.height - (localPos.y - origin.y)) :
                        static_cast<float>(size.y)) :
                    0.f)
        );

        border->reset(sf::FloatRect(0.f, 0.f, rectBorder.width, rectBorder.height));

        border->setViewport(sf::FloatRect(
            rectBorder.left / static_cast<float>(sizeTarget->x),
            rectBorder.top / static_cast<float>(sizeTarget->y),
            rectBorder.width / static_cast<float>(sizeTarget->x),
            rectBorder.height / static_cast<float>(sizeTarget->y)
        ));

        Transformable::setPosition(pos.x - rectBorder.left, pos.y - rectBorder.top);
    }

    updatedBorder = false;
}

void GUI::Object::updateFirstParent(Container* newFirstParent)
{
    firstParent = newFirstParent;
}

void GUI::Object::setTarget(sf::RenderTarget* target)
{
    if (!this->target && target) {
        this->target = target;
        updatedBorder = true;

        for (auto& connect : *connects)
            connect->setTarget(target);

        sizeTarget = target->getSize();
    }
}

bool GUI::Object::isPoint(float x, float y)
{
    Object* tmpObject = this;
    while (!tmpObject->border)
        tmpObject = tmpObject->parent ? tmpObject->parent : tmpObject->connect;

    return (x >= pos.x - origin.x && x <= pos.x - origin.x + static_cast<float>(size.x) &&
            y >= pos.y - origin.y && y <= pos.y - origin.y + static_cast<float>(size.y)) &&
            tmpObject->rectBorder.contains(x, y);
}

bool GUI::Object::isPoint(const sf::Vector2f& point)
{
    Object* tmpObject = this;
    while (!tmpObject->border)
        tmpObject = tmpObject->parent ? tmpObject->parent : tmpObject->connect;

    return (point.x >= pos.x - origin.x && point.x <= pos.x - origin.x + static_cast<float>(size.x) &&
            point.y >= pos.y - origin.y && point.y <= pos.y - origin.y + static_cast<float>(size.y)) &&
            tmpObject->rectBorder.contains(point.x, point.y);
}

const sf::Transform& GUI::Object::getTransform() const
{
    return Transformable::getTransform();
}

const sf::Transform& GUI::Object::getInverseTransform() const
{
    return Transformable::getInverseTransform();
}

void GUI::Object::connectObject(Object* object)
{
    object->remove();

    object->connect = this;
    connects->push_back(object);

    object->setPosition(object->localPos);
}

void GUI::Object::drawObject(Object* object, sf::RenderTarget& target, sf::RenderStates states) const
{
    if (object->border)
        target.setView(*object->border);

    target.draw(*object, states);

    const Object* tmpObject = this;
        while (!tmpObject->border)
            tmpObject = tmpObject->parent ? tmpObject->parent : tmpObject->connect;

    target.setView(*tmpObject->border);
}

void GUI::Object::handleIn()
{
    if (!disabled)
        handleInput();

    for (uint32_t i = connects->size(); i > 0U; i--)
        (*connects)[i - 1U]->handleIn();
}

void GUI::Object::handleEv(const sf::Event& event)
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
}

void GUI::Object::upd(float dt)
{
    if (border && updatedBorder)
        updateBorder();

    if (!disabled)
        update(dt);

    for (auto& connect : *connects)
        connect->upd(dt);

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

void GUI::Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if (!hidden)
        render(target, states);
}

void GUI::Object::handleInput() {}
void GUI::Object::handleEvent(const sf::Event& event) {}
void GUI::Object::update(float dt) {}
void GUI::Object::render(sf::RenderTarget& target, sf::RenderStates states) const {}

//Кастомные методы

void GUI::Object::customSetPosition(const sf::Vector2f& pos)
{
    localPos = pos;
}

void GUI::Object::customSetPosition(float x, float y)
{
    localPos = sf::Vector2f(x, y);
}

void GUI::Object::customSetSize(const sf::Vector2u& size)
{
    this->size = size;
}

void GUI::Object::customSetSize(uint32_t width, uint32_t height)
{
    size = sf::Vector2u(width, height);
}

void GUI::Object::customSetOrigin(const sf::Vector2f& origin)
{
    this->origin = origin;
}

void GUI::Object::customSetOrigin(float x, float y)
{
    origin = sf::Vector2f(x, y);
}

void GUI::Object::customSetRotation(float angle)
{
    this->angle = angle;
}

//Кастомное обновление трансформации

void GUI::Object::customUpdateTransform() {}

//Конструктор/Деструктор

GUI::Object::Object() 
    : firstParent(nullptr), parent(nullptr), index(-1), hidden(false), disabled(false),
      animations(new std::vector<Animation*>), target(nullptr),
      connect(nullptr), connects(new std::vector<Object*>), border(nullptr),
	  resize(false), reposition(false)
{
    setBorder(Application::object_on_border);

    indexObject = Application::allObject->size();
    Application::allObject->push_back(this);
}

GUI::Object::Object(const sf::Vector2f& pos, const sf::Vector2u& size)
    : firstParent(nullptr), parent(nullptr), index(-1), hidden(false), disabled(false),
      pos(pos), localPos(pos), size(size),
      animations(new std::vector<Animation*>), target(nullptr),
      connect(nullptr), connects(new std::vector<Object*>), border(nullptr),
	  resize(false), reposition(false)
{
    setBorder(Application::object_on_border);

    indexObject = Application::allObject->size();
    Application::allObject->push_back(this);
}

GUI::Object::Object(float x, float y, uint32_t width, uint32_t height)
    : firstParent(nullptr), parent(nullptr), index(-1), hidden(false), disabled(false),
      localPos(sf::Vector2f(x, y)), size(sf::Vector2u(width, height)),
      animations(new std::vector<Animation*>), target(nullptr),
      connect(nullptr), connects(new std::vector<Object*>), border(nullptr),
	  resize(false), reposition(false)
{
    pos = localPos;

    setBorder(Application::object_on_border);

    indexObject = Application::allObject->size();
    Application::allObject->push_back(this);
}

GUI::Object::~Object()
{
    remove();

    removeAnimations();

    delete animations;

    while (!connects->empty())
        (*connects)[0]->remove();

    delete connects;

    if (border)
        delete border;

    Application::allObject->erase(Application::allObject->begin() + indexObject);
    Application::updateIndex(indexObject);
}

//Геттеры

const GUI::Container* GUI::Object::getFirstParent() const
{
    return firstParent;
}

const GUI::Container* GUI::Object::getParent() const
{
    return parent;
}

uint32_t GUI::Object::getIndex() const
{
    return index;
}

bool GUI::Object::getHidden() const
{
    return hidden;
}

bool GUI::Object::getDisabled() const
{
    return disabled;
}

const sf::Vector2f& GUI::Object::getGlobalPosition() const
{
    return pos;
}

const sf::Vector2f& GUI::Object::getLocalPosition() const
{
    return localPos;
}

const sf::Vector2u& GUI::Object::getSize() const
{
    return size;
}

const sf::Vector2f& GUI::Object::getOrigin() const
{
    return origin;
}

float GUI::Object::getRotation() const
{
    return angle;
}

//Сеттеры

void GUI::Object::setBorder(bool onBorder)
{
    if (border)
        delete border;

    border = onBorder ? 
                new sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(size.x), static_cast<float>(size.y))) :
                nullptr;

    setPosition(localPos);
}

void GUI::Object::setHidden(bool hidden)
{
    this->hidden = hidden;
}

void GUI::Object::setDisabled(bool disabled)
{
    this->disabled = disabled;
}

void GUI::Object::setPosition(const sf::Vector2f& pos)
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

    customUpdateTransform();
}

void GUI::Object::setPosition(float x, float y)
{
    customSetPosition(x, y);

    if (parent)
        pos = parent->pos - parent->origin + localPos;
    else if (connect)
        pos = connect->pos - connect->origin + localPos;
    else
        pos = localPos;

    if (border) {
        Transformable::setPosition(0.f, 0.f);
        updatedBorder = true;
    } else
        Transformable::setPosition(localPos);

    for (auto& connect : *connects)
        connect->setPosition(connect->localPos);

    customUpdateTransform();
}

void GUI::Object::setSize(const sf::Vector2u& size)
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

    customUpdateTransform();
}

void GUI::Object::setSize(uint32_t width, uint32_t height)
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

    customUpdateTransform();
}

void GUI::Object::setOrigin(const sf::Vector2f& origin)
{
    if (origin.x >= 0.f && origin.x < size.x && origin.y >= 0.f && origin.y < size.y) {
        sf::Vector2f oldOrigin = this->origin;
        customSetOrigin(origin);

        setPosition(localPos - oldOrigin + this->origin);
        Transformable::setOrigin(this->origin);

        customUpdateTransform();
    }
}

void GUI::Object::setOrigin(float x, float y)
{
    if (x >= 0.f && x < size.x && y >= 0.f && y < size.y) {
        sf::Vector2f oldOrigin = origin;
        customSetOrigin(x, y);
        
        setPosition(localPos - oldOrigin + origin);
        Transformable::setOrigin(origin);

        customUpdateTransform();
    }
}

void GUI::Object::setRotation(float angle)
{
    customSetRotation(angle);
    Transformable::setRotation(this->angle);
    customUpdateTransform();
}

//Методы

void GUI::Object::resizeRelativeToTarget(bool resize)
{
    this->resize = resize;
}

void GUI::Object::repositionRelativeToTarget(bool reposition)
{
    this->reposition = reposition;
}

void GUI::Object::createAnimation(const std::function<void(const Animation&)> frameHandle, 
                                  const std::function<void()>& onFinish)
{
    animations->push_back(new Animation(frameHandle, onFinish));
}

void GUI::Object::changeAnimation(uint32_t index, const std::function<void(const Animation&)> frameHandle, 
                                  const std::function<void()>& onFinish)
{
    if (index < animations->size()) {
        delete (*animations)[index];
        (*animations)[index] = new Animation(frameHandle, onFinish);
    } else
        throw Error("Object::changeAnimation: Index more than the number of animations");
}

void GUI::Object::removeAnimation(uint32_t index)
{
    if (index < animations->size()) {
        delete (*animations)[index];
        animations->erase(animations->begin() + index);
    } else
        throw Error("Object::removeAnimation: Index more than the number of animations");
}

void GUI::Object::removeAnimations()
{
    if (!animations->empty())
        delete (*animations)[0];
    
    animations->clear();
}

void GUI::Object::moveForward()
{
    if (parent && index < parent->childrens->size() - 1U) {
        Object* tmp = (*parent->childrens)[index + 1];
        (*parent->childrens)[index + 1] = this;
        (*parent->childrens)[index] = tmp;

        tmp->index--;
        index++;
    }
}

void GUI::Object::moveBackward()
{
    if (parent && index > 0) {
        Object* tmp = (*parent->childrens)[index - 1];
        (*parent->childrens)[index - 1] = this;
        (*parent->childrens)[index] = tmp;

        tmp->index++;
        index--;
    }
}

void GUI::Object::moveToFront()
{
    if (parent) {
        size_t size = parent->childrens->size() - 1;
        while (index < size)
            moveForward();
    }
}

void GUI::Object::moveToBack()
{
    if (parent)
        while (index > 0U)
            moveBackward();
}

void GUI::Object::remove()
{
    if (parent) {
        parent->childrens->erase(parent->childrens->begin() + index);
        parent->updateIndex(index);

        parent = nullptr;
        firstParent = nullptr;
        index = -1;

        pos = localPos;

        target = nullptr;
    } else if (connect) {
        size_t size = connect->connects->size();
        for (uint32_t i = 0U; i < size; i++)
            if (this == (*connect->connects)[i]) {
                connect->connects->erase(connect->connects->begin() + i);
                break;
            }

        pos = localPos;

        connect = nullptr;
        target = nullptr;
    }
}

void GUI::Object::change(Object* obj)
{
    if (parent) {
        remove();
        parent->addChild(obj, index);
    }
}

void GUI::Object::move(const sf::Vector2f& offset)
{
    setPosition(localPos + offset);
}

void GUI::Object::move(float offsetX, float offsetY)
{
    setPosition(localPos.x + offsetX, localPos.y + offsetY);
}

void GUI::Object::scale(const sf::Vector2i& scaled)
{
    setSize((static_cast<int>(size.x) + scaled.x < 0) ? 0U : size.x + scaled.x, 
            (static_cast<int>(size.y) + scaled.y < 0) ? 0U : size.y + scaled.y);
}

void GUI::Object::scale(int scaledX, int scaledY)
{
    setSize((static_cast<int>(size.x) + scaledX < 0) ? 0U : size.x + scaledX,
            (static_cast<int>(size.y) + scaledY < 0) ? 0U : size.y + scaledY);
}

void GUI::Object::rotate(float angle)
{
    setRotation(this->angle + angle);
}