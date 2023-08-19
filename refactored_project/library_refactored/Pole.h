#include "Tile.h"


// this class represents a pole on the map
// the role of the robot is to find the poles
// and rember their position
class Pole
{
public:
    Pole(shared<Tile> tile) : currentTile_ = tile {}; 

private:
    shared<Tile> currentTile_;
};
