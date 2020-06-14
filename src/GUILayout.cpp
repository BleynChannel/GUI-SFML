#include "GUILayout.hpp"
#include "GUIError.hpp"

#include <string>

//Закрытые методы

uint32_t GUI::Layout::getAbsoluteTotalSize(const std::vector<Column>& array)
{
    uint32_t absoluteSize = 0U;
    for (auto& line : array)
        if (line.sizePolicy == SizePolicy::Absolute)
            absoluteSize += static_cast<uint32_t>(line.size);

    return absoluteSize;
}

void GUI::Layout::getCalculatedSize(Column& line, float dependency)
{
    line.calculatedSize = line.sizePolicy == SizePolicy::Relative ?
                                static_cast<uint32_t>(line.size * dependency) :
                                static_cast<uint32_t>(line.size);
}

void GUI::Layout::calculatePercentageSize(bool changingExistent, std::vector<Column>& array, uint32_t index)
{
    if (array[index].sizePolicy == SizePolicy::Relative) {
        float allPercents = 0.f, beforeFromIndexPercents = 0.f;
        
        uint32_t sizeArray = array.size();
        Column* line;
        for (uint32_t i = 0U; i < sizeArray; i++) {
            line = &array[i];

            allPercents += line->sizePolicy == SizePolicy::Relative ?
                                line->size :
                                0.f;

            beforeFromIndexPercents += (line->sizePolicy == SizePolicy::Relative && i <= index) ?
                                            line->size :
                                            0.f;
        }

        if (changingExistent && beforeFromIndexPercents > 1.f)
            throw Error("Layout::calculatePercentageSize: Layout summary percentage > 100% at index " + std::to_string(index));

        float modifyer = changingExistent ?
                            (1.f - beforeFromIndexPercents) / (allPercents - beforeFromIndexPercents) :
                            (1.f - array[index].size) / (allPercents - array[index].size);

        for (uint32_t i = changingExistent ? (index + 1U) : 0U; i < sizeArray; i++)
            array[i].size *= (array[i].sizePolicy == SizePolicy::Relative && i != index) ?
                                modifyer :
                                1.f;
    }
}

void GUI::Layout::update(float dt)
{
    if (positionChildrens->size() > childrens->size()) {
        uint32_t countRemove = 0U;
        uint32_t sizePosChildrens = positionChildrens->size();
        uint32_t sizeChildrens = childrens->size();

        Object* posObject;
        bool isMatche;

        for (uint32_t i = 0U; i < sizePosChildrens - countRemove; i++) {
            posObject = (*positionChildrens)[i].object;
            isMatche = false;

            for (uint32_t k = 0U; k < sizeChildrens; k++)
                if (posObject == (*childrens)[k])
                    isMatche = true;

            if (!isMatche) {
                positionChildrens->erase(positionChildrens->begin() + i);
                countRemove++;
            }
        }
    }

    if (updateLayout)
        update();
}

//Кастомное обновление трансформации

void GUI::Layout::customUpdateTransform()
{
    updateLayout = true;
}

//Конструктор/Деструктор

GUI::Layout::Layout(uint32_t columnCount, uint32_t rowCount)
    : grid(new std::vector<std::vector<Cell>>), columns(new std::vector<Column>), rows(new std::vector<Row>),
      positionChildrens(new std::vector<PositionObject>),
      defaultPositionColumn(Application::getLayoutDefaultPositionColumn()), 
      defaultPositionRow(Application::getLayoutDefaultPositionRow())
{
    setGridSize(columnCount, rowCount);
}

GUI::Layout::Layout(const sf::Vector2f& pos, const sf::Vector2u& size, uint32_t columnCount, uint32_t rowCount)
    : Container(pos, size), grid(new std::vector<std::vector<Cell>>), 
      columns(new std::vector<Column>), rows(new std::vector<Row>), positionChildrens(new std::vector<PositionObject>),
      defaultPositionColumn(Application::getLayoutDefaultPositionColumn()), 
      defaultPositionRow(Application::getLayoutDefaultPositionRow())
{
    setGridSize(columnCount, rowCount);
}

GUI::Layout::Layout(float x, float y, uint32_t width, uint32_t height, uint32_t columnCount, uint32_t rowCount)
    : Container(x, y, width, height), grid(new std::vector<std::vector<Cell>>), 
      columns(new std::vector<Column>), rows(new std::vector<Row>), positionChildrens(new std::vector<PositionObject>),
      defaultPositionColumn(Application::getLayoutDefaultPositionColumn()), 
      defaultPositionRow(Application::getLayoutDefaultPositionRow())
{
    setGridSize(columnCount, rowCount);
}

GUI::Layout::~Layout()
{
    delete rows;
    delete columns;
    delete grid;
}

//Геттеры

uint32_t GUI::Layout::getDefaultPositionColumn() const
{
    return defaultPositionColumn;
}

uint32_t GUI::Layout::getDefaultPositionRow() const
{
    return defaultPositionRow;
}

float GUI::Layout::getColumnWidth(uint32_t column) const
{
    if (column < columns->size())
        return (*columns)[column].size;
    
    throw Error("Layout::getColumnWidth: Index column more than the number of columns");
}

float GUI::Layout::getRowHeight(uint32_t row) const
{
    if (row < rows->size())
        return (*rows)[row].size;
    
    throw Error("Layout::getRowHeight: Index row more than the number of rows");
}

uint32_t GUI::Layout::getColumnCalculatedWidth(uint32_t column) const
{
    if (column < columns->size())
        return (*columns)[column].calculatedSize;
    
    throw Error("Layout::getColumnCalculatedWidth: Index column more than the number of columns");
}

uint32_t GUI::Layout::getRowCalculatedHeight(uint32_t row) const
{
    if (row < rows->size())
        return (*rows)[row].calculatedSize;
    
    throw Error("Layout::getRowCalculatedHeight: Index row more than the number of rows");
}

GUI::Layout::GridSize GUI::Layout::getGridSize() const
{
    return GridSize(columns->size(), rows->size());
}

const GUI::Layout::PositionObject& GUI::Layout::getPositionObject(Object* object) const
{
    for (auto& child : *positionChildrens)
        if (object == child.object)
            return child;

    throw Error("Layout::getPositionObject: The object is not children");
}

const GUI::Direction& GUI::Layout::getDirection(uint32_t column, uint32_t row) const
{
    if (column < columns->size() && row < rows->size())
        return (*grid)[row][column].direction;

    throw Error("Layout::getDirection: Index column or row more than the number of columns or rows");
}

uint32_t GUI::Layout::getSpacing(uint32_t column, uint32_t row) const
{
    if (column < columns->size() && row < rows->size())
        return (*grid)[row][column].spacing;

    throw Error("Layout::getSpacing: Index column or row more than the number of columns or rows");
}

const GUI::Alignment& GUI::Layout::getAlignment(uint32_t column, uint32_t row) const
{
    if (column < columns->size() && row < rows->size())
        return (*grid)[row][column].alignment;

    throw Error("Layout::getAlignment: Index column or row more than the number of columns or rows");
}

const GUI::Margin& GUI::Layout::getMargin(uint32_t column, uint32_t row) const
{
    if (column < columns->size() && row < rows->size())
        return (*grid)[row][column].margin;

    throw Error("Layout::getMargin: Index column or row more than the number of columns or rows");
}

const GUI::Fitting& GUI::Layout::getFitting(uint32_t column, uint32_t row) const
{
    if (column < columns->size() && row < rows->size())
        return (*grid)[row][column].fitting;

    throw Error("Layout::getFitting: Index column or row more than the number of columns or rows");
}

//Сеттеры

void GUI::Layout::setDefaultPositionColumn(uint32_t defaultPos)
{
    this->defaultPositionColumn = defaultPos;
}

void GUI::Layout::setDefaultPositionRow(uint32_t defaultPos)
{
    this->defaultPositionRow = defaultPos;
}

void GUI::Layout::setColumnWidth(uint32_t column, SizePolicy sizePolicy, float size)
{
    if (column < columns->size()) {
        Column& tmpColumn = (*columns)[column];

        tmpColumn.sizePolicy = sizePolicy;
        tmpColumn.size = size;

        calculatePercentageSize(true, *columns, column);

        updateLayout = true;
    } else
        throw Error("Layout::setColumnWidth: Index column more than the number of columns");
}

void GUI::Layout::setRowHeight(uint32_t row, SizePolicy sizePolicy, float size)
{
    if (row < rows->size()) {
        Row& tmpRow = (*rows)[row];

        tmpRow.sizePolicy = sizePolicy;
        tmpRow.size = size;

        calculatePercentageSize(true, *rows, row);

        updateLayout = true;
    } else
        throw Error("Layout::setRowHeight: Index row more than the number of rows");
}

void GUI::Layout::setGridSize(uint32_t columnCount, uint32_t rowCount)
{
    columnCount = !columnCount ? 1U : columnCount;
    rowCount = !rowCount ? 1U : rowCount;

    delete rows;
    delete columns;
    delete grid;

    grid = new std::vector<std::vector<Cell>>;
    columns = new std::vector<Column>;
    rows = new std::vector<Row>;

    for (uint32_t i = 1U; i <= rowCount; i++)
        addRow(SizePolicy::Relative, 1.f / i);

    for (uint32_t i = 1U; i <= columnCount; i++)
        addColumn(SizePolicy::Relative, 1.f / i);

    updateLayout = true;
}

void GUI::Layout::setGridSize(const GridSize& gridSize)
{
    uint32_t columnCount = !gridSize.columnCount ? 1U : gridSize.columnCount;
    uint32_t rowCount = !gridSize.rowCount ? 1U : gridSize.rowCount;

    delete rows;
    delete columns;
    delete grid;

    grid = new std::vector<std::vector<Cell>>;
    columns = new std::vector<Column>;
    rows = new std::vector<Row>;

    for (uint32_t i = 1U; i <= rowCount; i++)
        addRow(SizePolicy::Relative, 1.f / i);

    for (uint32_t i = 1U; i <= columnCount; i++)
        addColumn(SizePolicy::Relative, 1.f / i);

    updateLayout = true;
}

GUI::Object* GUI::Layout::setPositionObject(uint32_t column, uint32_t row, Object* object)
{
    for (auto& child : *positionChildrens)
        if (object == child.object) {
            child.column = column;
            child.row = row;
            
            updateLayout = true;
            break;
        }

    return object;
}

GUI::Object* GUI::Layout::setPositionObject(const PositionObject& positionObject)
{
    for (auto& child : *positionChildrens)
        if (positionObject.object == child.object) {
            child.column = positionObject.column;
            child.row = positionObject.row;

            updateLayout = true;
            break;
        }

    return positionObject.object;
}

void GUI::Layout::setDirection(uint32_t column, uint32_t row, Direction direction)
{
    if (column < columns->size() && row < rows->size()) {
        (*grid)[row][column].direction = direction;

        updateLayout = true;
    } else
        throw Error("Layout::setDirection: Index column or row more than the number of columns or rows");
}

void GUI::Layout::setSpacing(uint32_t column, uint32_t row, uint32_t spacing)
{
    if (column < columns->size() && row < rows->size()) {
        (*grid)[row][column].spacing = spacing;

        updateLayout = true;
    } else
        throw Error("Layout::setSpacing: Index column or row more than the number of columns or rows");
}

void GUI::Layout::setAlignment(uint32_t column, uint32_t row, AlignmentType horizontalAlignment, AlignmentType verticalAlignment)
{
    if (column < columns->size() && row < rows->size()) {
        Cell& cell = (*grid)[row][column];

        cell.alignment.horizontal = horizontalAlignment;
        cell.alignment.vertical = verticalAlignment;

        updateLayout = true;
    } else
        throw Error("Layout::setAlignment: Index column or row more than the number of columns or rows");
}

void GUI::Layout::setAlignment(uint32_t column, uint32_t row, const Alignment& alignment)
{
    if (column < columns->size() && row < rows->size()) {
        (*grid)[row][column].alignment = alignment;
        
        updateLayout = true;
    } else
        throw Error("Layout::setAlignment: Index column or row more than the number of columns or rows");
}

void GUI::Layout::setMargin(uint32_t column, uint32_t row, uint32_t horizontalMargin, uint32_t verticalMargin)
{
    if (column < columns->size() && row < rows->size()) {
        Cell& cell = (*grid)[row][column];

        cell.margin.horizontal = horizontalMargin;
        cell.margin.vertical = verticalMargin;

        updateLayout = true;
    } else
        throw Error("Layout::setMargin: Index column or row more than the number of columns or rows");
}

void GUI::Layout::setMargin(uint32_t column, uint32_t row, const Margin& margin)
{
    if (column < columns->size() && row < rows->size()) {
        (*grid)[row][column].margin = margin;

        updateLayout = true;
    } else
        throw Error("Layout::setMargin: Index column or row more than the number of columns or rows");
}

void GUI::Layout::setFitting(uint32_t column, uint32_t row, bool horizontalFitting, bool verticalFitting,
                        uint32_t horizontalOffset, uint32_t verticalOffset)
{
    if (column < columns->size() && row < rows->size()) {
        Cell& cell = (*grid)[row][column];

        cell.fitting.horizontal = horizontalFitting;
        cell.fitting.vertical = verticalFitting;
        cell.fitting.horizontalOffset = horizontalOffset;
        cell.fitting.verticalOffset = verticalOffset;

        updateLayout = true;
    } else
        throw Error("Layout::setFitting: Index column or row more than the number of columns or rows");
}

void GUI::Layout::setFitting(uint32_t column, uint32_t row, const Fitting& fitting)
{
    if (column < columns->size() && row < rows->size()) {
        (*grid)[row][column].fitting = fitting;
        updateLayout = true;
    } else
        throw Error("Layout::setFitting: Index column or row more than the number of columns or rows");
}

void GUI::Layout::setFittingOffset(uint32_t column, uint32_t row, uint32_t horizontal, uint32_t vertical)
{
    if (column < columns->size() && row < rows->size()) {
        Cell& cell = (*grid)[row][column];

        cell.fitting.horizontalOffset = horizontal;
        cell.fitting.verticalOffset = vertical;

        updateLayout = true;
    } else
        throw Error("Layout::setFittingOffset: Index column or row more than the number of columns or rows");
}

//Методы

void GUI::Layout::addColumn(SizePolicy sizePolicy, float size)
{
    uint32_t newSizeColumn = columns->size() + 1U;

    uint32_t sizeRow = rows->size();
    for (uint32_t row = 0U; row < sizeRow; row++)
        (*grid)[row].resize(newSizeColumn);

    columns->push_back(Column(sizePolicy, size));

    calculatePercentageSize(false, *columns, columns->size() - 1U);

    updateLayout = true;
}

void GUI::Layout::addRow(SizePolicy sizePolicy, float size)
{
    grid->resize(rows->size() + 1U);

    rows->push_back(Row(sizePolicy, size));

    calculatePercentageSize(false, *rows, rows->size() - 1U);

    updateLayout = true;
}

void GUI::Layout::removeColumn(uint32_t column)
{
    if (column < columns->size()) {
        uint32_t sizeRow = rows->size();
        for (uint32_t row = 0U; row < sizeRow; row++)
            (*grid)[row].erase((*grid)[row].begin() + column);

        (*columns)[column].size = 0.f;
        calculatePercentageSize(false, *columns, column);

        columns->erase(columns->begin() + column);

        updateLayout = true;
    } else
        throw Error("Layout::removeColumn: Index column more than the number of columns");
}

void GUI::Layout::removeRow(uint32_t row)
{
    if (row < rows->size()) {
        grid->erase(grid->begin() + row);

        (*rows)[row].size = 0.f;
        calculatePercentageSize(false, *rows, row);

        rows->erase(rows->begin() + row);

        updateLayout = true;
    } else
        throw Error("Layout::removeRow: Index row more than the number of rows");
}

void GUI::Layout::fitToChildrenSize(uint32_t column, uint32_t row)
{
    if (column < columns->size() && row < rows->size()) {
        uint32_t width = 0U, height = 0U;

        Cell* cell = &(*grid)[row][column];
        const sf::Vector2u* sizeChild;

        for (auto& child : *childrens) {
            sizeChild = &child->getSize();

            width = !child->getHidden() ?
                        (cell->direction == Direction::Horizontal ?
                            (width + sizeChild->x + cell->spacing) :
                            (width > sizeChild->x ? width : sizeChild->x)) :
                        width;

            height = !child->getHidden() ?
                        (cell->direction == Direction::Horizontal ?
                            (height > sizeChild->y ? height : sizeChild->y) :
                            (height + sizeChild->y + cell->spacing)) :
                        height;
        }

        width -= cell->direction == Direction::Horizontal ?
                    cell->spacing :
                    0U;
        
        height -= cell->direction == Direction::Vertical ?
                    cell->spacing :
                    0U;

        setSize(width, height);

        updateLayout = true;
    } else
        throw Error("Layout::fitToChildrenSize: Index column or row more than the number of columns or rows");
}

void GUI::Layout::update()
{
    float columnPercentageTotalSize = static_cast<float>(size.x - getAbsoluteTotalSize(*columns));
    float rowPercentageTotalSize = static_cast<float>(size.y - getAbsoluteTotalSize(*rows));

    Cell* cell;
    uint32_t sizeChildrens = positionChildrens->size();

    uint32_t sizeColumn = columns->size(), sizeRow = rows->size();
    for (uint32_t row = 0U; row < sizeRow; row++) {
        getCalculatedSize((*rows)[row], rowPercentageTotalSize);
        
        for (uint32_t column = 0U; column < sizeColumn; column++) {
            getCalculatedSize((*columns)[column], columnPercentageTotalSize);

            cell = &(*grid)[row][column];

            cell->countChildToCell = 0U;

            for (auto& child : *positionChildrens)
                if (child.column == column && child.row == row)
                    cell->countChildToCell++;

            cell->childsWidth = 0U;
            cell->childsHeight = 0U;
        }
    }

    sf::Vector2u sizeChild;

    for (auto& child : *positionChildrens)
        if (!child.object->getHidden()) {
            if (child.row >= 0U && child.row < sizeRow && child.column >= 0U && child.column < sizeColumn) {
                cell = &(*grid)[child.row][child.column];
                sizeChild = child.object->getSize();

                sizeChild.x = cell->fitting.horizontal ?
                                    (((*columns)[child.column].calculatedSize - cell->fitting.horizontalOffset) /
                                        (cell->direction == Direction::Horizontal ?
                                            cell->countChildToCell :
                                            1U)) :
                                    sizeChild.x;

                sizeChild.y = cell->fitting.vertical ?
                                    (((*rows)[child.row].calculatedSize - cell->fitting.verticalOffset) /
                                        (cell->direction == Direction::Vertical ?
                                            cell->countChildToCell :
                                            1U)) :
                                    sizeChild.y;
                
                if (cell->fitting.horizontal || cell->fitting.vertical)
                    child.object->setSize(sizeChild);

                cell->childsWidth = cell->direction == Direction::Horizontal ?
                                        (cell->childsWidth + sizeChild.x + cell->spacing) :
                                        (cell->childsWidth > sizeChild.x ? cell->childsWidth : sizeChild.x);

                cell->childsHeight = cell->direction == Direction::Vertical ?
                                        (cell->childsHeight + sizeChild.y + cell->spacing) :
                                        (cell->childsHeight > sizeChild.y ? cell->childsHeight : sizeChild.y);
            } else {
                child.object->setDisabled(true);
                child.object->setHidden(true);
            }
        }

    float x = 0.f, y = 0.f;
    uint32_t calcWidth, calcHeight;

    for (uint32_t row = 0U; row < sizeRow; row++) {
        for (uint32_t column = 0U; column < sizeColumn; column++) {
            cell = &(*grid)[row][column];
            calcWidth = (*columns)[column].calculatedSize;
            calcHeight = (*rows)[row].calculatedSize;

            cell->pos = cell->alignment.getCoordinates(
                x, y, calcWidth, calcHeight,
                cell->childsWidth - (cell->direction == Direction::Horizontal ? cell->spacing : 0U),
                cell->childsHeight - (cell->direction == Direction::Vertical ? cell->spacing : 0U)
            );

            if (cell->margin.horizontal || cell->margin.vertical)
                cell->pos = cell->margin.getCoordinates(
                    cell->pos, 
                    cell->alignment.horizontal, cell->alignment.vertical
                );

            x += static_cast<float>(calcWidth);
        }

        x = 1.f, y += static_cast<float>(calcHeight);
    }

    sf::Vector2f alignmentPos;
    float newChildX, newChildY;

    for (auto& child : *positionChildrens)
        if (!child.object->getHidden()) {
            cell = &(*grid)[child.row][child.column];
            sizeChild = child.object->getSize();

            alignmentPos = cell->alignment.getCoordinates(
                cell->pos.x, cell->pos.y,
                cell->childsWidth, cell->childsHeight,
                sizeChild.x, sizeChild.y
            );

            newChildX = cell->direction == Direction::Horizontal ?
                            cell->pos.x :
                            alignmentPos.x;

            newChildY = cell->direction == Direction::Vertical ?
                            cell->pos.y :
                            alignmentPos.y;

            cell->pos.x += cell->direction == Direction::Horizontal ?
                                (sizeChild.x + cell->spacing) :
                                0.f;

            cell->pos.y += cell->direction == Direction::Vertical ?
                                (sizeChild.y + cell->spacing) :
                                0.f;

            child.object->setPosition(newChildX, newChildY);
        }

    updateLayout = false;
}

//Container

GUI::Object* GUI::Layout::addChild(Object* obj)
{
    if (obj) {
        Container::addChild(obj);
        positionChildrens->push_back(PositionObject(defaultPositionColumn, defaultPositionRow, obj));
        updateLayout = true;
    }

    return obj;
}

GUI::Object* GUI::Layout::addChild(Object* obj, uint32_t index)
{
    if (obj) {
        Container::addChild(obj, index);
        positionChildrens->push_back(PositionObject(defaultPositionColumn, defaultPositionRow, obj));
        updateLayout = true;
    }

    return obj;
}

void GUI::Layout::removeChildren(uint32_t index)
{
    if (index < childrens->size()) {
        Object* tmpChild = (*childrens)[index];
        uint32_t sizePosChildrens = positionChildrens->size();

        for (uint32_t i = 0U; i < sizePosChildrens; i++)
            if (tmpChild == (*positionChildrens)[i].object)
                positionChildrens->erase(positionChildrens->begin() + i);

        tmpChild->remove();

        updateLayout = true;
    } else
        throw Error("Index more than the number of childrens");
}

void GUI::Layout::removeChildrens(uint32_t fromIndex)
{
    size_t sizeChildrens = childrens->size(), sizePosChildrens;
    Object* tmpChild;
    for (uint32_t i = fromIndex; i < sizeChildrens; i++) {
        tmpChild = (*childrens)[i];
        
        sizePosChildrens = positionChildrens->size();
        for (uint32_t k = 0U; k < sizePosChildrens; k++)
            if (tmpChild == (*positionChildrens)[k].object)
                positionChildrens->erase(positionChildrens->begin() + k);

        tmpChild->remove();

        updateLayout = true;
    }
}

void GUI::Layout::removeChildrens(uint32_t fromIndex, uint32_t toIndex)
{
    toIndex = toIndex < childrens->size() ? toIndex : childrens->size() - 1U;

    size_t sizePosChildrens;
    Object* tmpChild;
    for (uint32_t i = fromIndex; i <= toIndex; i++) {
        tmpChild = (*childrens)[i];
        
        sizePosChildrens = positionChildrens->size();
        for (uint32_t k = 0U; k < sizePosChildrens; k++)
            if (tmpChild == (*positionChildrens)[k].object)
                positionChildrens->erase(positionChildrens->begin() + k);

        tmpChild->remove();

        updateLayout = true;
    }
}