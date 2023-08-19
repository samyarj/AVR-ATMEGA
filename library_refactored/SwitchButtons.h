#include "IOPorts.h"


// A class to control the switch buttons of the robot
class SwitchButton : public IOPorts
{
public:
    SwitchButton();
    virtual ~SwitchButton() = 0;

    virtual bool isOn() = 0;
    virtual void initializeSwitch() = 0;

    virtual void filterPress() { filterRebound(true); } //filter rebound when button pressed
    virtual void filterRelease() { filterRebound(false); } //filter rebound when button released

protected:
    virtual void filterRebound(bool press);
    
    volatile uint8_t *_ddr;
    volatile uint8_t *_pin;
    uint8_t _bit;

private:
    const uint8_t _reboundDelay = 10;
};


class InterruptButton : public SwitchButton
{
public:
    InterruptButton() : SwitchButton() {};
    virtual ~InterruptButton() = default;

    virtual bool isOn();
    virtual void initializeSwitch();

protected:
    volatile uint8_t *_ddr = &DDRD;
    volatile uint8_t *_pin = &PIND;
    uint8_t _bit = 2;
};


// this button is activated when switched to 0, not 1 (reverse logic)
class WhiteButton : public SwitchButton
{
public:
    WhiteButton() : SwitchButton() {};
    virtual ~WhiteButton() = default;

    virtual bool isOn();
    virtual void initializeSwitch();

protected:
    volatile uint8_t *_ddr = &DDRC;
    volatile uint8_t *_pin = &PINC;
    uint8_t _bit = 0;
};

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
