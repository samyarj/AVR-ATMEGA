#include "LED.h"

LED::LED()
{
    activateOutMode();
}

LED::~LED()
{
    activateInMode();
}

void LED::eteindre()
{
    togglePort(_mode00);
}

void LED::allumerRouge()
{
    togglePort(_mode01);
}

void LED::allumerVert()
{
    togglePort(_mode10);
}
