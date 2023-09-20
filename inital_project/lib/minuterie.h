#ifndef MINUTERIE_H
#define MINUTERIE_H
#include <avr/io.h>
#include <util/delay.h>
#include "controlPort.h"

class Minuterie : public ControlPort
{
public:
    Minuterie() = default;
    ~Minuterie() = default;
    void partirMinuterieModeCTC(uint32_t duree);
    void initialisation(void);

private:
    uint32_t _DEUX_SECONDES_MINUTERIE = 15625;
    uint32_t _RAPPORT_2SEC_MS = 2000;
    volatile uint8_t _gMinuterieExpiree = 0;
    volatile uint8_t *_DDR_MINUTERIE = &DDRD;
    uint8_t _BIT_MINUTERIE = 5;
    uint8_t _MODE_SORTIE = 1;
};
#endif