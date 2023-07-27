#include "SwitchButtons.h"

SwitchButton::SwitchButton() : IOPorts()
{
    activateInMode();
}

void SwitchButton::filterRebound(bool press)
{
    while (true)
    {
        if (!(isOn() ^ press))
        {
            _delay_ms(_reboundDelay);
            if (!(isOn() ^ press))
                break;
        }
    }
}

bool InterruptButton::isOn()
{
    return (*_pin) & generateMask(_bit, _mode01);
}

void InterruptButton::initializeSwitch()
{
    cli();
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

bool WhiteButton::isOn()
{
    return !((*_pin) & generateMask(_bit, _mode01));
}

void WhiteButton::initializeSwitch()
{
    cli();
    PCMSK2 |= (1 << PCINT16);
    PCICR |= (1 << PCIE2);
    sei();
}
