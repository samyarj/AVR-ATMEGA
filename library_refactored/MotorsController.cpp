#include "MotorsController.h"

MotorsController::MotorsController() : IOPorts()
{
    activateOutMode();
    selectPWMFrequency(_frequency);
    // division d'horloge par 8 - implique une fréquence de PWM fixe
    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
}

MotorsController::~MotorsController()
{
    activateInMode();
    TCCR0A &= ~(1 << WGM00);
    TCCR0A &= ~((1 << COM0A1) | (1 << COM0B1));
}

void MotorsController::setIOMode(uint8_t wantedMode)
{
    setPort(_ddr, _bit - 1, wantedMode); //modified since there is 2 motors to control
    setPort(_ddr, _bit + 1, wantedMode);
}

void MotorsController::chooseMovement(uint8_t leftWheelDirection, uint8_t rightWheelDirection)
{
    setPort(_port, _bit - 1, leftWheelDirection);
    setPort(_port, _bit + 2, rightWheelDirection);
}

uint8_t MotorsController::generatePWMMask(uint8_t wantedBit, uint8_t mask)
{
    // Mask (PORTX &= 11100011)
    if (mask == _masque000)
        return (~((1 << wantedBit) | (1 << (wantedBit + 1)) | (1 << (wantedBit + 2))));
    // Mask (PORTX |= XXX001XX)
    else if (mask == _masque001)
        return (1 << wantedBit);
    // Mask (PORTX |= XXX011XX)
    else if (mask == _masque011)
        return ((1 << wantedBit) | (1 << (wantedBit + 1)));
    // Mask (PORTX |= XXX101X)
    else
        return ((1 << wantedBit) | (1 << (wantedBit + 2)));
}

void MotorsController::selectPWMFrequency(Frequency frequency)
{
    switch (frequency)
    {
    case Frequency::f15HZ:
        TCCR0B &= generatePWMMask(CS10, _masque000);
        TCCR0B |= generatePWMMask(CS10, _masque101);
        break;

    case Frequency::f61HZ:
        TCCR0B &= generatePWMMask(CS10, _masque000);
        TCCR0B |= generatePWMMask(CS12, _masque001);
        break;

    case Frequency::f245HZ:
        TCCR0B &= generatePWMMask(CS10, _masque000);
        TCCR0B |= generatePWMMask(CS10, _masque011);
        break;

    case Frequency::f1961HZ:
        TCCR0B &= generatePWMMask(CS10, _masque000);
        TCCR0B |= generatePWMMask(CS11, _masque001);
        break;

    case Frequency::f15686HZ:
        TCCR0B &= generatePWMMask(CS10, _masque000);
        TCCR0B |= generatePWMMask(CS10, _masque001);
        break;
    }
}

void MotorsController::adjustSpeed(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    OCR0A = leftWheelSpeed;
    OCR0B = rightWheelSpeed;
}

void MotorsController::moveForward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    chooseMovement(_forward, _forward);
    adjustSpeed(leftWheelSpeed, rightWheelSpeed);
}

void MotorsController::moveBackward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    chooseMovement(_backward, _backward);
    adjustSpeed(leftWheelSpeed, rightWheelSpeed);
}

void MotorsController::turnLeft(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    chooseMovement(_backward, _forward);
    adjustSpeed(leftWheelSpeed, rightWheelSpeed);
}

void MotorsController::turnRight(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    chooseMovement(_forward, _backward);
    adjustSpeed(leftWheelSpeed, rightWheelSpeed);
}

void MotorsController::stopMotor()
{
    adjustSpeed(0, 0);
    _delay_ms(700); //to give time to friction to stop the movement before the next command
}

void MotorsController::turnLeft90() //use to adjust the position of the robot without detecting obstacles
{
    turnLeft(255, 255);
    _delay_ms(80);
    adjustSpeed(100, 95);
    _delay_ms(800);
    stopMotor();
}

void MotorsController::turnRight90() //use to adjust the position of the robot without detecting obstacles
{
    turnRight(255, 255);
    _delay_ms(80);
    adjustSpeed(100, 95);
    _delay_ms(800);
    stopMotor();
}
