#ifndef SOUND_H
#define SOUND_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "IOPorts.h"

class Sound : public IOPorts
{
public:
    Sound();
    virtual ~Sound();
    uint16_t convertNote(uint8_t givenNote);
    void startSound(uint16_t givenNote);
    void stopSound();

protected:
    volatile uint8_t *_port = &PORTD;
    volatile uint8_t *_ddr = &DDRD;
    uint8_t _bit = 6;

private:
    const uint16_t CPU_PRESCALER_ = 15625; // (F_CPU/256*2)
};

#endif
