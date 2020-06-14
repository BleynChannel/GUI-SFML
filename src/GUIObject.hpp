#pragma once

#include "GUIApplication.hpp"
#include "GUIAnimation.hpp"

namespace GUI 
{

    class Container;

    class Object : private sf::Drawable, private sf::Transformable
    {
    private:
        uint32_t indexObject;
        sf::View* border;
        sf::FloatRect rectBorder;
        sf::RenderTarget* target;
        sf::Vector2u sizeTarget;
        bool updatedBorder;

        void updateBorder();

        virtual void updateFirstParent(Container* newFirstParent);
        virtual void setTarget(sf::RenderTarget* target);
        virtual void handleIn();
        virtual void handleEv(const sf::Event& event);
        virtual void upd(float dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    protected:
        Container* firstParent;
        Container* parent;
        uint32_t index;

        Object* connect;
        std::vector<Object*>* connects;

        std::vector<Animation*>* animations;

        bool hidden;
        bool disabled;
        bool resize;
		bool reposition;

        sf::Vector2f pos;
        sf::Vector2f localPos;
        sf::Vector2u size;
        sf::Vector2f origin;
        float angle;

        //Закрытые методы
        bool isPoint(float x, float y);
        bool isPoint(const sf::Vector2f& point);
		const sf::Transform& getTransform() const;
        const sf::Transform& getInverseTransform() const;

        void connectObject(Object* object);
        void drawObject(Object* object, sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void handleInput();
        virtual void handleEvent(const sf::Event& event);
        virtual void update(float dt);
        virtual void render(sf::RenderTarget& target, sf::RenderStates states) const;

        //Кастомные методы
        virtual void customSetPosition(const sf::Vector2f& pos);
        virtual void customSetPosition(float x, float y);
        virtual void customSetSize(const sf::Vector2u& size);
        virtual void customSetSize(uint32_t width, uint32_t height);
        virtual void customSetOrigin(const sf::Vector2f& origin);
        virtual void customSetOrigin(float x, float y);
        virtual void customSetRotation(float angle);

        //Кастомное обновление трансформации
        virtual void customUpdateTransform();
    public:
        //Конструктор/Деструктор
        Object();
        Object(const sf::Vector2f& pos, const sf::Vector2u& size);
        Object(float x, float y, uint32_t width, uint32_t height);
        virtual ~Object();

        //Геттеры
        virtual const Container* getFirstParent() const;
        virtual const Container* getParent() const;
        virtual uint32_t getIndex() const;

        virtual bool getHidden() const;
        virtual bool getDisabled() const;

        virtual const sf::Vector2f& getGlobalPosition() const;
        virtual const sf::Vector2f& getLocalPosition() const;
        virtual const sf::Vector2u& getSize() const;
        virtual const sf::Vector2f& getOrigin() const;
        virtual float getRotation() const;

        //Сеттеры
        virtual void setBorder(bool onBorder);

        virtual void setHidden(bool hidden);
        virtual void setDisabled(bool disabled);

        virtual void setPosition(const sf::Vector2f& pos);
        virtual void setPosition(float x, float y);
        virtual void setSize(const sf::Vector2u& size);
        virtual void setSize(uint32_t width, uint32_t height);
        void setOrigin(const sf::Vector2f& origin);
        void setOrigin(float x, float y);
        void setRotation(float angle);

        //Методы
        virtual void resizeRelativeToTarget(bool resize);
		virtual void repositionRelativeToTarget(bool reposition);

        virtual void createAnimation(const std::function<void(const Animation&)> frameHandle, 
                                     const std::function<void()>& onFinish = nullptr);
        virtual void changeAnimation(uint32_t index, const std::function<void(const Animation&)> frameHandle, 
                                     const std::function<void()>& onFinish = nullptr);
        virtual void removeAnimation(uint32_t index);
        virtual void removeAnimations();

        virtual void moveForward();
        virtual void moveBackward();
        virtual void moveToFront();
        virtual void moveToBack();

        virtual void remove();
        virtual void change(Object* obj);

        void move(const sf::Vector2f& offset);
        void move(float offsetX, float offsetY);
        void scale(const sf::Vector2i& scaled);
        void scale(int scaledX, int scaledY);
        void rotate(float angle);

        friend Application;
        friend Container;
        friend Workspace;
    };
}