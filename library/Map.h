#include "Tile.h"

class Map
{
public:
    Map(uint32_t width, uint32_t lenght);
    ~Map() = default;

    std::shared_ptr<Tile> getTile(uint32_t key);

    // this method gives neighbours to Tiles.
    void parseTiles();

private:
    int tileCounter_ = 1; // stores total number of tiles
    std::unordered_map<uint32_t, std::shared_ptr<Tile>> tiles_;
    uint32_t width_;
    uint32_t lenght_;
};


/* algo for finding neighbours

general formula to find an id: id= (length)*lineNum + columnNum + 1
assuming bottomLeft is 1
formula topRight: id = width * lenght
formula topLeft: id = topRight - length + 1 or (length)*(width-1) + 1
formula bottomRight: id = length

`parseTitles()`
Conditions: for tile : tiles_{}
Angle 0: if (isUnderTopRow(id)) tile->setVoisins(0, id+length)

Angle 45: if (isUnderTopRow(id) && isNotRightColumn(id)) tile->setVoisins(1, id+length+1)
`parseTitles()`

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