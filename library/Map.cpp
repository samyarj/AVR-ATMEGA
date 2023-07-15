#include "Map.h"

Map::Map(uint32_t width, uint32_t lenght) : width_(width), lenght_(lenght)
{
    for (uint32_t i = 0; i < width; ++i)
    {
        for (uint32_t j = 0; j < lenght; ++j)
        {
            uint32_t key = this->tileCounter_;
            tiles_[key] = std::make_shared<Tile>(i, j);
            this->tileCounter_++;
        }
    }
}

std::shared_ptr<Tile> Map::getTile(uint32_t key)
{
    if (tiles_.find(key) != tiles_.end())
        return std::move(tiles_[key]);
    else
        return nullptr;
}
