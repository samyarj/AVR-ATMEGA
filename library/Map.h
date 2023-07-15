#include "Tile.h"
#include <string>
#include <unordered_map>
#include <memory>

class Map
{
public:
    Map(uint8_t width, uint8_t lenght): width_(width), lenght_(lenght)
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
    ~Map() = default;

    std::unique_ptr<Tile> getTile(uint8_t key)
    {
        if (tiles_.find(key) != tiles_.end())
            return std::move(tiles_[key]);
        else
            return nullptr;
    }

private:
    int tileCounter_ = 0;  // stores total number of tiles
    std::unordered_map<uint8_t, std::unique_ptr<Tile>> tiles_;
    uint8_t width_;
    uint8_t lenght_;
};


/* algo for finding neighbours

general formula to find an id: id= (length)*lineNum + columnNum
assuming bottomLeft is 0
formula topRight: id = width * lenght - 1
formula topLeft: id = topRight - length + 1 or (length)*(width-1)
formula bottomRight: id = length - 1

`parseTitles()`
Conditions: for tile : tiles_{}
Angle 0: if (isUnderTopRow(id)) tile->setVoisins(0, id+length)

Angle 45: if (isUnderTopRow(id) && isNotRightColumn(id)) tile->setVoisins(1, id+length+1)

Angle 90: if (isNotRightColumn(id)) tile->setVoisins(2, id++)

Angle 135: if (isOverBottomRow(id) && isNotRightColumn(id)) tile->setVoisins(3, id-length+1)

Angle 180: if (isOverBottomRow(id)) tile->setVoisins(4, id-length)

Angle 225: if (isOverBottomRow(id) && isNotLeftColumn(id)) tile->setVoisins(5, id-length-1)

Angle 270: if (isNotLeftColumn(id)) tile->setVoisins(6, id--)

Angle 315: if (isUnderTopRow(id) && isNotLeftColumn(id)) tile->setVoisins(7, id+length-1)

bool isUnderTopRow(uint8_t id) { id < topLeft;}
bool isNotRightColumn(uint8_t id) { (id % bottomRight) != 0;}
bool isOverBottomRow(uint8_t id) {id > bottomRight;}
bool isNotLeftColumn(uint8_t id) {(id % length) != 0;}

*/