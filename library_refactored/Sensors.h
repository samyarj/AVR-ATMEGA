#include "can.h"
#include "IOPorts.h"

class Sensors : public IOPorts
{
public:
    Sensors();
    virtual ~Sensors() = default;

    uint16_t getDistance(); //returns a value between 0 and 255, the bigger the number the closer the object detected

protected:
    volatile uint8_t *_port = &PORTA;
    volatile uint8_t *_ddr = &DDRA;
    uint8_t _bit = 4;

private:
    can &can_; //from can.h
    const uint8_t sizeSample_ = 10;

    uint16_t distance;
};
