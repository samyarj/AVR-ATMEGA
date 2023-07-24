#include "Map.h"

Map::Map(uint32_t width, uint32_t length) : width_(width), length_(length)
{
    for (uint32_t i = 0; i < width; ++i)
    {
        for (uint32_t j = 0; j < length; ++j)
        {
            uint32_t key = this->tileCounter_;
            tiles_[key] = std::make_shared<Tile>(i, j);
            this->tileCounter_++;
        }
    }
}

std::shared_ptr<Tile> Map::getTile(uint32_t key) 
{
    auto it = tiles_.find(key);
    if(it != tiles_.end()) 
        return it->second;
    else
        return nullptr;
}

void Map::parseTiles() 
{
    for(auto& pair : tiles_)
    {
        uint32_t id = pair.first;
        auto& tile = pair.second;

        if (isUnderTopRow(id)) tile->setNeighbour(0, id+width_);
        if (isUnderTopRow(id) && isNotRightColumn(id)) tile->setNeighbour(45, id+width_+1);
        if (isNotRightColumn(id)) tile->setNeighbour(90, id+1);
        if (isOverBottomRow(id) && isNotRightColumn(id)) tile->setNeighbour(135, id-width_+1);
        if (isOverBottomRow(id)) tile->setNeighbour(180, id-width_);
        if (isOverBottomRow(id) && isNotLeftColumn(id)) tile->setNeighbour(225, id-width_-1);
        if (isNotLeftColumn(id)) tile->setNeighbour(270, id-1);
        if (isUnderTopRow(id) && isNotLeftColumn(id)) tile->setNeighbour(315, id+width_-1);
    }
}
