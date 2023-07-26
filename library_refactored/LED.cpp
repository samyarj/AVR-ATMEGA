#include "LED.h"

LED::LED()
{
    activateOutMode();
}

LED::~LED()
{
    activateInMode();
}

