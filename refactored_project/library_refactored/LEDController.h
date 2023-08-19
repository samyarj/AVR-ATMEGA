#include "IOPorts.h"


// A class to control the LED of the robot
class LEDController : public IOPorts
{
public:
    LEDController();
    virtual ~LEDController();

    void turnOff();
    void turnRed();
    void turnGreen();

    void turnAmber(uint32_t iterations); // iteration = number of repetitions of 250us for red-green cycle

    void turnAmberMs(uint32_t delay); // delay in milliseconds
    void turnAmberS(uint32_t delay);  // delay in seconds

    void startFlashing();
    void stopFlashing();
    void flashLED();

protected:
    uint32_t calculateIterations(uint32_t delay, uint32_t unity);

    volatile uint8_t *_port = &PORTA;
    volatile uint8_t *_ddr = &DDRA;
    uint8_t _bit = 0;
    volatile bool _switch = true;

private:
    uint32_t _LEDFrequency = 4000; // constant for the calculateIterations
    // 4000Hz, since the cycle red-green of the turnAmber method takes 250us (4000*250*10⁻6 = 1 sec)
};

//**NECESSARY CODE BELOW TO ENABLE FLASHING FUNCTION**

//Possibility to put it in on the main app file

// LEDController l;

// ISR(TIMER1_COMPA_vect)
// {
//     l.flashLED();
// }
