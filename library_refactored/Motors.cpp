#include "Motors.h"

Motors::Motors()
{
    activateOutMode();
    // division d'horloge par 8 - implique une fréquence de PWM fixe
    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
}

void Motors::setIOMode(uint8_t wantedMode)
{
    setPort(_ddr, _bit - 1, wantedMode); //modified since there is 2 motors to control
    setPort(_ddr, _bit + 1, wantedMode);
}

void Motors::chooseMovement(uint8_t leftWheelDirection, uint8_t rightWheelDirection)
{
    setPort(_port, _bit - 1, leftWheelDirection);
    setPort(_port, _bit + 2, rightWheelDirection);
}

void Motors::moveForward(uint8_t speed)
{
    chooseMovement(_forward, _forward);
    //select frequency
    //adjust speed
}

void Motors::moveBackward(uint8_t speed)
{
    chooseMovement(_backward, _backward);
}

void Motors::turnLeft(uint8_t speed)
{
    chooseMovement(_backward, _forward);
}

void Motors::turnRight(uint8_t speed)
{
    chooseMovement(_forward, _backward);
}
