#include "Tile.h"
#include "Pole.h"

#include "LED.h"
#include "memoire_24.h"
#include "Motors.h"
#include "RS232communication.h"
#include "Sensors.h"
#include "Sound.h"
#include "SwitchButtons.h"

class Robot
{
public:
    Robot(Tile* initTile, int16_t initAngle_) 
    : currentTile_(initTile), currentAngle_(initAngle_) {};
    
    void updateTile(Tile* nextTile) { currentTile_ = nextTile; };
    void changeAngle(int16_t rotationAngle);  // changes currentAngle_  
    void initializeAngle(int16_t initAngle);  // initialize currentAngle_
    
    int getNextTileKey(); // calls `Tile::getNeighbourKey(this->currentAngle_)`

private:
    Tile* currentTile_;
    int16_t currentAngle_;
    vector<Pole*> detectedPoles_;

    LED* m_led;
    Motors* m_motors;
    Sensors* m_sensors;
    Sound* m_sound;
    InterruptButton* m_iButton;
    WhiteButton* m_wButton;
    friend class RobotController;
};
