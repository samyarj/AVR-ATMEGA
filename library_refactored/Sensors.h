#include "can.h"
#include "IOPorts.h"

class Sensors : public IOPorts
{
public:
    Sensors();
    virtual ~Sensors() = default;

    uint16_t getDistance(); //returns a value between 0 and 255, the bigger the number the closer the object detected
    bool distanceUnder15cm(); //checks if object is closer than 15cm to the sensor
    bool distanceUnder30cm(); //checks if object is closer than 30cm to the sensor
    bool distanceUnder60cm(); //checks if object is closer than 60cm to the sensor

protected:
    volatile uint8_t *_port = &PORTA;
    volatile uint8_t *_ddr = &DDRA;
    uint8_t _bit = 4;

private:
    can can_; //from can.h
    const uint8_t sizeSample_ = 10;

    //tested experimentally
    const uint16_t distance15cm_ = 110;
    const uint16_t distance30cm_ = 45;
    const uint16_t distance60cm_ = 13;

};
