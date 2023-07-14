#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "minuterie.h"

void Minuterie::partirMinuterieModeCTC(uint32_t duree) // en millisecondes
{
    _gMinuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0;
    OCR1A = (duree * _DEUX_SECONDES_MINUTERIE) / _RAPPORT_2SEC_MS;
    TCCR1A |= (1 << COM1A0);
    TCCR1B |= (1 << CS12) | (1 << CS10); // diviser par 1024 cycles
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
}

void Minuterie::initialisation(void)
{
    cli();
    setPort(_DDR_MINUTERIE, _BIT_MINUTERIE, _MODE_SORTIE);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}