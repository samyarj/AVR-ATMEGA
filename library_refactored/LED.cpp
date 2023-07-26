#include "LED.h"

LED::LED()
{
    activateOutMode();
}

LED::~LED()
{
    activateInMode();
}

void LED::turnOff()
{
    togglePort(_mode00);
}

void LED::turnRed()
{
    togglePort(_mode01);
}

void LED::turnGreen()
{
    togglePort(_mode10);
}

uint32_t LED::calculateIterations(uint32_t delay, uint32_t unity)
{
    return (_LEDFrequency * delay) / unity;
}

void LED::turnAmber(uint32_t iterations)
{
    for (uint32_t i{0}; i < iterations; i++) // 250us per cycle
    {
        turnRed();
        _delay_us(31);
        turnGreen();
        for (int i = 0; i < 3; i++)
            _delay_us(73);
        // repeat 3 times since the precision of this function decreases for values over 100
    }
}

void LED::turnAmberMs(uint32_t delay)
{
    turnAmber(calculateIterations(delay, 1000)); // for a delay in milliseconds
}

void LED::turnAmberS(uint32_t delay)
{
    turnAmber(calculateIterations(delay, 1)); // for a delay in seconds
}
