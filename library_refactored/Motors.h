#include "IOPorts.h"

class Motors : public IOPorts
{
public:
    virtual void setIOMode(uint8_t wantedMode);

    void moveForward(uint8_t speed);
    void moveBackward(uint8_t speed);
    void turnLeft(uint8_t speed);
    void turnRight(uint8_t speed);

protected:
    void chooseMovement(uint8_t leftWheelDirection, uint8_t rightWheelDirection);
    
    volatile uint8_t *_port = &PORTB;
    volatile uint8_t *_ddr = &DDRB;
    uint8_t _bit = 3;

private:
    uint8_t _forward = 0;
    uint8_t _backward = 1;
};
