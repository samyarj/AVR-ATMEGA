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

void RobotController::detectAndTurn(int repetitions)
{
    adjustSpeedMotor(100, 95);
    for (int k = 0; k < repetitions; k++) //the robot turns for ~repetitions*100ms 
    {
        if (obstacleUnder60cm()) break; //to stop midway if an obstacle is detected 
        _delay_ms(100); //the _delay_ms function can't take a variable as a parameter, only a constant
    }
    stopMotor();
}

void RobotController::initLeft()
{
    if (!obstacleUnder60cm())
    {
        turnLeft(255, 255); //max speed to overcome static friction
        _delay_ms(40);
    }
}

void RobotController::initRight()
{
    if (!obstacleUnder60cm())
    {
        turnRight(255, 255); //max speed to overcome static friction
        _delay_ms(40);
    }
}

//tested experimentally
void RobotController::detectAndTurnLeft10() //initially 5
{
    initLeft();
    detectAndTurn(2); //2 repetitions gives approximately 10 degrees in rotation
}

void RobotController::detectAndTurnRight10() //initially 5
{
    initRight();
    detectAndTurn(2);
}

void RobotController::detectAndTurnLeft15() //initially 10
{
    initLeft();
    detectAndTurn(3); //3 repetitions gives approximately 15 degrees
}
    
void RobotController::detectAndTurnRight15() //initially 10
{
    initRight();
    detectAndTurn(3); //3 repetitions gives approximately 15 degrees
}
    
void RobotController::detectAndTurnLeft25() //initially 15
{
    initLeft();
    detectAndTurn(5); //5 repetitions gives approximately 25 degrees
}

void RobotController::detectAndTurnRight25() //initially 15
{
    initRight();
    detectAndTurn(5); //5 repetitions gives approximately 25 degrees
}

void RobotController::detectAndTurnLeft60() //initially 45
{
    initLeft();
    detectAndTurn(10); //10 repetitions gives approximately 60 degrees
}

void RobotController::detectAndTurnRight60() //initially 45
{
    initRight();
    detectAndTurn(10); //10 repetitions gives approximately 60 degrees
}

void RobotController::turnLeft90()
{
    motors_->turnLeft90();
}
    
void RobotController::turnRight90()
{
    motors_->turnRight90();
}

void RobotController::moveToPole()
{

}
