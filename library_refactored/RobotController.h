#include "LED.h"
#include "memoire_24.h"
#include "Motors.h"
#include "RS232communication.h"
#include "Sensors.h"
#include "Sound.h"
#include "SwitchButtons.h"

class RobotController
{
public:
    RobotController() = default;
    
    void turnLEDOff();
    void turnLEDRed();
    void turnLEDGreen();
    void turnLEDAmber(uint32_t delay); //in ms
    void startFlashingLED();
    void stopFLashingLED();
    void flashLED();

    void adjustSpeedMotor(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void moveForward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void moveBackward(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void turnLeft(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void turnRight(uint8_t leftWheelSpeed, uint8_t rightWheelSpeed);
    void stopMotor();

    bool obstacleUnder15cm(); 
    bool obstacleUnder30cm(); 
    bool obstacleUnder60cm(); 

    void startSound(uint16_t givenNote);
    void stopSound();

    bool interruptButtonIsOn();
    void initializeInterruptButton();
    void filterPressInterruptButton();
    void filterReleaseInterruptButton();

    bool whiteButtonIsOn();
    void initializeWhiteButton();
    void filterPressWhiteButton();
    void filterReleaseWhiteButton();

    //tested experimentally
    void detectAndTurn(int repetitions);
    void RobotController::initLeft();
    void RobotController::initRight();

    void detectAndTurnLeft10();
    void detectAndTurnRight10();
    void detectAndTurnLeft15();
    void detectAndTurnRight15();
    void detectAndTurnLeft25();
    void detectAndTurnRight25();
    void detectAndTurnLeft60();
    void detectAndTurnRight60();

    void turnLeft90();
    void turnRight90();

    void moveToPole();
    
private:
    LED* led_;
    Motors* motors_;
    Sensors* sensors_;
    Sound* sound_;
    InterruptButton* iButton_;
    WhiteButton* wButton_;
};

//**NECESSARY CODE BELOW TO ENABLE FLASHING FUNCTION**

//Possibility to put it in on the main app file

//Robot* r = new Robot;
//RobotController controller(r);

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
