#include "Robot.h"
#include "Robot.h"

class RobotController
{
public:
    RobotController(Robot* robot) : robot_(robot) {}
    
    void turnLEDOff();
    void turnLEDRed();
    void turnLEDGreen();
    void turnLEDAmber(uint32_t delay);
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

    virtual bool interruptButtonIsOn();
    virtual void initializeInterruptButton();
    virtual void filterPressInterruptButton();
    virtual void filterReleaseInterruptButton();

    virtual bool whiteButtonIsOn();
    virtual void initializeWhiteButton();
    virtual void filterPressWhiteButton();
    virtual void filterReleaseWhiteButton();
    
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
