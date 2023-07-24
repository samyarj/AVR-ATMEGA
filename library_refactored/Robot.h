#include "Tile.h"
#include "Pole.h"

class Robot
{
public:
    Robot(Tile* initTile, uint16_t initAngle_) 
    : currentTile_(initTile), currentAngle_(initAngle_) {};

    void updateTile(Tile* nextTile) { currentTile_ = nextTile; };
    void changeAngle(uint16_t rotationAngle);  // changes currentAngle_  
    
    int getNextTileKey(); // calls `Tile::getNeighbourKey(this->currentAngle_)`

private:
    Tile* currentTile_;
    uint16_t currentAngle_;
    vector<Pole*> detectedPoles_;
};
