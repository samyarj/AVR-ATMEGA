#include "RobotController.h"

void RobotController::turnLEDOff()
{
    led_->turnOff();
}
    
void RobotController::turnLEDRed()
{
    led_->turnRed();
}

void RobotController::turnLEDGreen()
{
    led_->turnGreen();
}
    
void RobotController::turnLEDAmber(uint32_t delay)
{
    led_->turnAmberMs(delay);
}

void RobotController::startFlashingLED()
{
    led_->startFlashing();
}

void RobotController::stopFLashingLED()
{
    led_->stopFlashing();
}
    
void RobotController::flashLED()
{
    led_->flashLED();
}

void RobotController::adjustSpeedMotor(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    motors_->adjustSpeed(leftWheelSpeed, rightWheelSpeed);
}
    
void RobotController::moveForward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    motors_->moveForward(leftWheelSpeed, rightWheelSpeed);
}

void RobotController::moveBackward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    motors_->moveBackward(leftWheelSpeed, rightWheelSpeed);
}

void RobotController::turnLeft(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    motors_->turnLeft(leftWheelSpeed, rightWheelSpeed);
}

void RobotController::turnRight(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    motors_->turnRight(leftWheelSpeed, rightWheelSpeed);
}

void RobotController::stopMotor()
{
    motors_->stopMotor();
}

bool RobotController::obstacleUnder15cm()
{
    return sensors_->distanceUnder15cm();
} 

bool RobotController::obstacleUnder30cm()
{
    return sensors_->distanceUnder30cm();
} 

bool RobotController::obstacleUnder60cm()
{
    sensors_->distanceUnder60cm();
} 

void RobotController::startSound(uint16_t givenNote)
{
    sound_->startSound(givenNote);
}

void RobotController::stopSound()
{
    sound_->stopSound();
}

bool RobotController::interruptButtonIsOn()
{
    return iButton_->isOn();
}

void RobotController::initializeInterruptButton()
{
    iButton_->initializeSwitch();
}

void RobotController::filterPressInterruptButton()
{
    iButton_->filterPress();
}
    
void RobotController::filterReleaseInterruptButton()
{
    iButton_->filterRelease();
}

bool RobotController::whiteButtonIsOn()
{
    return wButton_->isOn();
}
    
void RobotController::initializeWhiteButton()
{
    wButton_->initializeSwitch();
}

void RobotController::filterPressWhiteButton()
{
    wButton_->filterPress();
}
    
void RobotController::filterReleaseWhiteButton()
{
    wButton_->filterRelease();
}