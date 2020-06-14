#pragma once

#include "GUIContainer.hpp"
#include "GUIToolKit.hpp"

namespace GUI
{

    class Layout : public Container
    {
    public:
        struct GridSize
        {
            uint32_t columnCount, rowCount;

            GridSize() 
                : columnCount(Application::getLayoutDefaultColumnCount()), 
                  rowCount(Application::getLayoutDefaultRowCount()) {};
            GridSize(uint32_t columnCount, uint32_t rowCount) : columnCount(columnCount), rowCount(rowCount) {}
        };
        struct PositionObject
        {
            Object* object;
            uint32_t column, row;

            PositionObject() : column(1U), row(1U), object(nullptr) {}
            PositionObject(uint32_t column, uint32_t row, Object* object) : column(column), row(row), object(object) {}
        };
    protected:
        struct Cell 
        {
            Direction direction;
            uint32_t spacing;
            Alignment alignment;
            Margin margin;
            Fitting fitting;

            uint32_t childsWidth, childsHeight;
            sf::Vector2f pos;
            uint32_t countChildToCell;

            Cell() : direction(Direction::Vertical), spacing(1) {}
        };
        struct Column
        {
            SizePolicy sizePolicy;
            float size;
            uint32_t calculatedSize;

            Column(SizePolicy sizePolicy, float size) : sizePolicy(sizePolicy), size(size) {}
        };
        typedef Column Row;
    protected:
        std::vector<std::vector<Cell>>* grid;
        std::vector<Column>* columns;
        std::vector<Row>* rows;
        std::vector<PositionObject>* positionChildrens;

        uint32_t defaultPositionColumn;
        uint32_t defaultPositionRow;

        bool updateLayout;

        //Закрытые методы
        uint32_t getAbsoluteTotalSize(const std::vector<Column>& array);
        void getCalculatedSize(Column& line, float dependency);
        void calculatePercentageSize(bool changingExistent, std::vector<Column>& array, uint32_t index);

        virtual void update(float dt) override;

        //Кастомное обновление трансформации
        virtual void customUpdateTransform() override;
    public:
        //Конструктор/Деструктор
        Layout(uint32_t columnCount = Application::getLayoutDefaultColumnCount(),
               uint32_t rowCount = Application::getLayoutDefaultRowCount());
        Layout(const sf::Vector2f& pos, const sf::Vector2u& size, 
               uint32_t columnCount = Application::getLayoutDefaultColumnCount(),
               uint32_t rowCount = Application::getLayoutDefaultRowCount());
        Layout(float x, float y, uint32_t width, uint32_t height, 
               uint32_t columnCount = Application::getLayoutDefaultColumnCount(),
               uint32_t rowCount = Application::getLayoutDefaultRowCount());
        virtual ~Layout();

        //Геттеры
        virtual uint32_t getDefaultPositionColumn() const;
        virtual uint32_t getDefaultPositionRow() const;
        virtual float getColumnWidth(uint32_t column) const;
        virtual float getRowHeight(uint32_t row) const;
        virtual uint32_t getColumnCalculatedWidth(uint32_t column) const;
        virtual uint32_t getRowCalculatedHeight(uint32_t row) const;

        virtual GridSize getGridSize() const;

        virtual const PositionObject& getPositionObject(Object* object) const;
        virtual const Direction& getDirection(uint32_t column, uint32_t row) const;
        virtual uint32_t getSpacing(uint32_t column, uint32_t row) const;
        virtual const Alignment& getAlignment(uint32_t column, uint32_t row) const;
        virtual const Margin& getMargin(uint32_t column, uint32_t row) const;
        virtual const Fitting& getFitting(uint32_t column, uint32_t row) const;

        //Сеттеры
        virtual void setDefaultPositionColumn(uint32_t defaultPos);
        virtual void setDefaultPositionRow(uint32_t defaultPos);
        virtual void setColumnWidth(uint32_t column, SizePolicy sizePolicy, float size);
        virtual void setRowHeight(uint32_t row, SizePolicy sizePolicy, float size);

        virtual void setGridSize(uint32_t columnCount, uint32_t rowCount);
        virtual void setGridSize(const GridSize& gridSize);

        virtual Object* setPositionObject(uint32_t column, uint32_t row, Object* object);
        virtual Object* setPositionObject(const PositionObject& positionObject);
        virtual void setDirection(uint32_t column, uint32_t row, Direction direction);
        virtual void setSpacing(uint32_t column, uint32_t row, uint32_t spacing);
        virtual void setAlignment(uint32_t column, uint32_t row, AlignmentType horizontalAlignment, AlignmentType verticalAlignment);
        virtual void setAlignment(uint32_t column, uint32_t row, const Alignment& Alignment);
        virtual void setMargin(uint32_t column, uint32_t row, uint32_t horizontalMargin, uint32_t verticalMargin);
        virtual void setMargin(uint32_t column, uint32_t row, const Margin& margin);
        virtual void setFitting(uint32_t column, uint32_t row, bool horizontalFitting, bool verticalFitting,
                                uint32_t horizontalOffset = 0, uint32_t verticalOffset = 0);
        virtual void setFitting(uint32_t column, uint32_t row, const Fitting& fitting);
        virtual void setFittingOffset(uint32_t column, uint32_t row, uint32_t horizontal, uint32_t vertical);

        //Методы
        virtual void addColumn(SizePolicy sizePolicy, float size);
        virtual void addRow(SizePolicy sizePolicy, float size);
        virtual void removeColumn(uint32_t column);
        virtual void removeRow(uint32_t row);

        virtual void fitToChildrenSize(uint32_t column, uint32_t row);

        void update();

        //Container
        virtual Object* addChild(Object* obj) override;
        virtual Object* addChild(Object* obj, uint32_t index) override;

        virtual void removeChildren(uint32_t index) override;

        virtual void removeChildrens(uint32_t fromIndex = 0U) override;
        virtual void removeChildrens(uint32_t fromIndex, uint32_t toIndex) override;
    };
}