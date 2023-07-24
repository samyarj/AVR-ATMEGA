#include "Tile.h"

void Tile::setNeighbour(uint8_t angle, int idNeighbour)
{
    if (angleToIndex_.count(angle) == 1) {
        neighbours_[angleToIndex_.at(angle)] = idNeighbour;
    }
    else
        cout << "invalide input" << endl; 
}

int getNeighbourKey(uint16_t angle)
{
    return neighbours_[angleToIndex_.at(angle)];
}