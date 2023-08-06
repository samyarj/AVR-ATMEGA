#include "LEDController.h"

LEDController::LEDController()
{
    activateOutMode();
}

LEDController::~LEDController()
{
    activateInMode();
}

void LEDController::turnOff()
{
    togglePort(_mode00);
}

void LEDController::turnRed()
{
    togglePort(_mode01);
}

void LEDController::turnGreen()
{
    togglePort(_mode10);
}

uint32_t LEDController::calculateIterations(uint32_t delay, uint32_t unity)
{
    return (_LEDFrequency * delay) / unity;
}

void LEDController::turnAmber(uint32_t iterations)
{
    for (uint32_t i{0}; i < iterations; i++)  // 250us per cycle
    {
        turnRed();
        _delay_us(31);
        turnGreen();
        
        // repeat 3 times since the precision of this function decreases for values over 100
        for (int i = 0; i < 3; i++)
            _delay_us(73);
    }
}

void LEDController::turnAmberMs(uint32_t delay)
{
    turnAmber(calculateIterations(delay, 1000)); // for a delay in milliseconds
}

void LEDController::turnAmberS(uint32_t delay)
{
    turnAmber(calculateIterations(delay, 1)); // for a delay in seconds
}

void LEDController::startFlashing()
{
    TCCR1B |= (1 << WGM12);               // mode CTC
    TIMSK1 |= (1 << OCIE1A);              // Enable compare match interrupt
    OCR1A = 390;                          // compare each second interrupt at 16MHz clock
    TCCR1B |= (1 << CS12) | (1 << CS10);  // prescaler = 1024
}

void LEDController::stopFlashing()
{
    TIMSK1 &= ~(1 << OCIE1A); // disable compare match interrupt// prescaler = 1024
}

void LEDController::flashLED()
{
    _switch ^= 1;
    if (_switch)
        turnRed();
    else
        turnOff();
}
