#include "IOPorts.h"

class LED : public IOPorts
{
public:
    LED();
    virtual ~LED();

    void turnOff();
    void turnRed();
    void turnGreen();

    void turnAmber(uint32_t iterations);

    void turnAmberMs(uint32_t delay); //delay in milliseconds
    void turnAmberS(uint32_t delay); //delay in seconds

protected:
    uint32_t calculateIterations(uint32_t delay, uint32_t unity);
    
    volatile uint8_t *_port = &PORTA;
    volatile uint8_t *_ddr = &DDRA;
    uint8_t _bit = 0;

private:
    uint32_t _LEDFrequency = 4000; //constant for the calculateIterations
    //4000Hz, since the cycle red-green of the turnAmber method takes 250us (4000*250*10⁻6 = 1 sec)
};
