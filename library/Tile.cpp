#include "Tile.h"

void Tile::setNeighbour(uint8_t angle, int idNeighbour)
{
    if (angleToIndex_.count(angle) > 0) {
        neighbours_[angleToIndex_.at(angle)] = idNeighbour;
    }
    else
        cout << "invalide input" << endl; 
}
