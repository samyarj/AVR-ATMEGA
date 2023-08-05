#include "Tile.h"
#include "Pole.h"

class RobotTracker
{
public:
    RobotTracker(Tile* initTile, int16_t initAngle_) 
    : currentTile_(initTile), currentAngle_(initAngle_) {};
    
    void updateTile(Tile* nextTile) { currentTile_ = nextTile; };
    void changeAngle(int16_t rotationAngle);  // changes currentAngle_  
    void initializeAngle(int16_t initAngle);  // initialize currentAngle_
    
    int getNextTileKey(); // calls `Tile::getNeighbourKey(this->currentAngle_)`

private:
    Tile* currentTile_;
    int16_t currentAngle_;
    vector<Pole*> detectedPoles_;
};
