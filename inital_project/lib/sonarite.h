#ifndef SONARITE_H
#define SONARITE_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "controlPort.h"

class Sonarite : public ControlPort
{
public:
    Sonarite();
    uint16_t convertirNote(uint8_t noteDonnee);
    void commencerSon(uint16_t frequence_note);
    void arreterSon();

private:
    const uint16_t CPU_PRESCALER_ = 15625; // (F_CPU/256*2)
};

#endif
