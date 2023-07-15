#include "Map.h"

Map::Map(uint8_t width, uint8_t lenght) : width_(width), lenght_(lenght)
{
    for (uint8_t i = 0; i < width; ++i)
    {
        for (uint8_t j = 0; j < lenght; ++j)
        {
            uint8_t key = this->tileCounter_;
            tiles_[key] = std::make_unique<Tile>(i, j);
            this->tileCounter_++;
        }
    }
}

std::unique_ptr<Tile> Map::getTile(uint8_t key)
{
    if (tiles_.find(key) != tiles_.end())
        return std::move(tiles_[key]);
    else
        return nullptr;
}
