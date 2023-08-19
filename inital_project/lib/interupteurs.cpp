#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define PORT_DEL &PORTA
#define DDR_DEL &DDRA
#define PIN_INTERRUPTEUR &PIND
#define DDR_INTERRUPTEUR &DDRD
#include "interupteurs.h"

bool Interupt::verifierPIN()
{
    return (*_PIN_INTERRUPTEUR) & genererMask(_BIT_INTERRUPTEUR, _BIT1_ALLUMER);
}

void Interupt::filtreAntiRebondScrutation(bool appuyer)
{
    while (true)
    {
        if (!(verifierPIN() ^ appuyer))
        {
            delai(_DELAI_ANTIREBOND, facteurMs());
            if (!(verifierPIN() ^ appuyer))
                break;
        }
    }
}

void Interupt::initialisationInterrupt()
{
    cli();
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

bool BoutonBlanc::verifierPIN()
{
    return !((*_PIN_INTERRUPTEUR) & genererMask(_BIT_INTERRUPTEUR, _BIT1_ALLUMER));
}

void BoutonBlanc::filtreAntiRebondScrutation(bool appuyer)
{
    while (true)
    {
        if (!(verifierPIN() ^ appuyer))
        {
            delai(_DELAI_ANTIREBOND, facteurMs());
            if (!(verifierPIN() ^ appuyer))
                break;
        }
    }
}

void BoutonBlanc::initialisationInterrupt()
{
    cli();
    PCMSK2 |= (1 << PCINT16);
    PCICR |= (1 << PCIE2);
    sei();
}
