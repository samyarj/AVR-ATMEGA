#include "IOPorts.h"

enum class Frequency
    {
        f15HZ,
        f61HZ,
        f245HZ,
        f1961HZ,
        f15686HZ
    };

class Motors : public IOPorts
{
public:
    Motors(Frequency frequency);
    virtual ~Motors();

    void chooseMovement(uint8_t leftWheelDirection, uint8_t rightWheelDirection);
    void selectPWMFrequency(Frequency frequency);

    //speed values range from 0 to 255, the bigger the faster. 
    //Values from 0 to 70 might not do any movement if the friction of the wheels is too high
    //the speed of the wheels can be chosen indepently
    void adjustSpeed(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);

    //practical fonctions for client classes
    void moveForward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void moveBackward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void turnLeft(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void turnRight(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);

protected:
    virtual void setIOMode(uint8_t wantedMode);
    uint8_t generatePWMMask(uint8_t wantedBit, uint8_t mask);
    
    volatile uint8_t *_port = &PORTB;
    volatile uint8_t *_ddr = &DDRB;
    uint8_t _bit = 3;

private:
    uint8_t _forward = 0;
    uint8_t _backward = 1;

    uint8_t _masque000 = 0;
    uint8_t _masque001 = 1;
    uint8_t _masque011 = 2;
    uint8_t _masque101 = 3;
    
};
