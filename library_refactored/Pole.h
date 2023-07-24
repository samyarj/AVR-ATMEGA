#include "Tile.h"

class Pole
{
public:
    Pole(shared<Tile> tile) : currentTile_ = tile {}; 

private:
    shared<Tile> currentTile_;
};
