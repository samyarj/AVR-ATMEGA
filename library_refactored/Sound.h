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
    uint16_t convertNote(uint8_t givenNote);
    void startSound(uint16_t noteFrequency);
    void stopSound();

private:
    const uint16_t CPU_PRESCALER_ = 15625; // (F_CPU/256*2)
};

#endif
