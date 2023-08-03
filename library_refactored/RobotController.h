#include "Robot.h"
#include "Robot.h"

class RobotController
{
public:
    RobotController(Robot* robot) : robot_(robot) {}
    
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
    
private:
    Robot* robot_;
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
