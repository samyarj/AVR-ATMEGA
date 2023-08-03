#include "RobotController.h"

void RobotController::turnLEDOff()
{
    robot_->led_->turnOff();
}
    
void RobotController::turnLEDRed()
{
    robot_->led_->turnRed();
}

void RobotController::turnLEDGreen()
{
    robot_->led_->turnGreen();
}
    
void RobotController::turnLEDAmber(uint32_t delay)
{
    robot_->led_->turnAmberMs(delay);
}

void RobotController::startFlashingLED()
{
    robot_->led_->startFlashing();
}

void RobotController::stopFLashingLED()
{
    robot_->led_->stopFlashing();
}
    
void RobotController::flashLED()
{
    robot_->led_->flashLED();
}

void RobotController::adjustSpeedMotor(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    robot_->motors_->adjustSpeed(leftWheelSpeed, rightWheelSpeed);
}
    
void RobotController::moveForward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    robot_->motors_->moveForward(leftWheelSpeed, rightWheelSpeed);
}

void RobotController::moveBackward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    robot_->motors_->moveBackward(leftWheelSpeed, rightWheelSpeed);
}

void RobotController::turnLeft(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    robot_->motors_->turnLeft(leftWheelSpeed, rightWheelSpeed);
}

void RobotController::turnRight(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed)
{
    robot_->motors_->turnRight(leftWheelSpeed, rightWheelSpeed);
}

void RobotController::stopMotor()
{
    robot_->motors_->stopMotor();
}

bool RobotController::obstacleUnder15cm()
{
    return robot_->sensors_->distanceUnder15cm();
} 

bool RobotController::obstacleUnder30cm()
{
    return robot_->sensors_->distanceUnder30cm();
} 

bool RobotController::obstacleUnder60cm()
{
    robot_->sensors_->distanceUnder60cm();
} 

void RobotController::startSound(uint16_t givenNote)
{
    robot_->sound_->startSound(givenNote);
}

void RobotController::stopSound()
{
    robot_->sound_->stopSound();
}

bool RobotController::interruptButtonIsOn()
{
    return robot_->iButton_->isOn();
}

void RobotController::initializeInterruptButton()
{
    robot_->iButton_->initializeSwitch();
}

void RobotController::filterPressInterruptButton()
{
    robot_->iButton_->filterPress();
}
    
void RobotController::filterReleaseInterruptButton()
{
    robot_->iButton_->filterRelease();
}

bool RobotController::whiteButtonIsOn()
{
    return robot_->wButton_->isOn();
}
    
void RobotController::initializeWhiteButton()
{
    robot_->wButton_->initializeSwitch();
}

void RobotController::filterPressWhiteButton()
{
    robot_->wButton_->filterPress();
}
    
void RobotController::filterReleaseWhiteButton()
{
    robot_->wButton_->filterRelease();
}