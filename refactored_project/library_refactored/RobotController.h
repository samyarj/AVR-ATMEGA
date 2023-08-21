#include "LEDController.h"
#include "memoire_24.h"
#include "MotorsController.h"
#include "RS232communication.h"
#include "Sensors.h"
#include "SoundController.h"
#include "SwitchButtons.h"


// A class to control the robot
// this class is the facade of the robot
// under the hood, it uses the other classes
// that control the different parts of the robot
// it is the only class that should be used by the client
class RobotController
{
public:
    RobotController();
    ~RobotController();
    
    //LED Controller methods
    void turnLEDOff();
    void turnLEDRed();
    void turnLEDGreen();
    void turnLEDAmber(uint32_t delay); //in ms
    void startFlashingLED();
    void stopFLashingLED();
    void flashLED();

    //Sensors methods
    bool obstacleUnder15cm(); 
    bool obstacleUnder30cm(); 
    bool obstacleUnder60cm(); 

    //Sound Controller methods
    void startSound(uint16_t givenNote);
    void stopSound();

    //InterruptButton methods
    bool interruptButtonIsOn();
    void initializeInterruptButton();
    void filterPressInterruptButton();
    void filterReleaseInterruptButton();

    //whiteButton methods
    bool whiteButtonIsOn();
    void initializeWhiteButton();
    void filterPressWhiteButton();
    void filterReleaseWhiteButton();

    // used by RobotManager for its algorithms (MotorsController methods)
    void advanceToPole();
    void rotateToPoleLeft45();
    void rotateToPoleRight45();
    void turnLeft90();
    void turnRight90();
    
private:
    LEDController* led_;
    MotorsController* motors_;
    Sensors* sensors_;
    SoundController* sound_;
    InterruptButton* iButton_;
    WhiteButton* wButton_;

    void adjustSpeedMotor(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void moveForward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void moveBackward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void turnLeft(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void turnRight(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void stopMotor();
    
    void detectAndTurn(int repetitions);
    void RobotController::initLeft();
    void RobotController::initRight();

    //tested experimentally
    void detectAndTurnLeft10();
    void detectAndTurnRight10();
    void detectAndTurnLeft25();
    void detectAndTurnRight25();
    void detectAndTurnLeft60();
    void detectAndTurnRight60();
};

//**NECESSARY CODE BELOW TO ENABLE FLASHING FUNCTION**

//Possibility to put it in on the main app file

//RobotController controller;

// ISR(TIMER1_COMPA_vect)
// {
//     controller.flashLED();
// }


//**NECESSARY CODE BELOW IF THE INTERRUPTION CAN HAPPEN ANYTIME**

//Interrupt Button rebound filter
// ISR(INT0_vect)
// {
//   _delay_ms(30); //rebound delay
//   //does something
//   EIFR |= (1 << INTF0);
// }

// //White Button rebound filter
// ISR(PCINT2_vect)
// {
//   _delay_ms(30);//rebound delay
//   //does something
//   PCIFR |= (1 << PCIF2);
// }
