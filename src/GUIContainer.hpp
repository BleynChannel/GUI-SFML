#pragma once

#include "GUIObject.hpp"

namespace GUI
{
    class Container : public Object
    {
    private:
        void updateIndex(uint32_t fromIndex);
        void updateFirstParent(Container* newFirstParent) override;
        void setTarget(sf::RenderTarget* target) override;
        void handleIn() override;
        void handleEv(const sf::Event& event) override;
        void upd(float dt) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    protected:
        std::vector<Object*>* childrens;
    public:
        //Конструктор/Деструктор
        Container();
        Container(const sf::Vector2f& pos, const sf::Vector2u& size);
        Container(float x, float y, uint32_t width, uint32_t height);
        virtual ~Container();

        //Методы
        virtual Object* addChild(Object* obj);
        virtual Object* addChild(Object* obj, uint32_t index);

        virtual void removeChildren(uint32_t index);

        virtual void removeChildrens(uint32_t fromIndex = 0U);
        virtual void removeChildrens(uint32_t fromIndex, uint32_t toIndex);

        virtual Object* getChildren(uint32_t index);
        virtual std::vector<Object*>& getChildrens();

        //Object
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        void setSize(const sf::Vector2u& size);
        void setSize(uint32_t width, uint32_t height);

        friend Object;
        friend Workspace;
    };
}