#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "sonarite.h"
#include <unordered_map>

Sonarite::Sonarite()
{
    setPort(&DDRD, 6, 3);
    setPort(&PORTD, 6, 0);
}

void Sonarite::commencerSon(uint16_t frequence_note)
{
    TCNT2 = 0;
    OCR2A = (CPU_PRESCALER_ / (frequence_note)) - 1;
    TCCR2A = (1 << COM2A0) | (1 << WGM21); // compare match,  Mode CTC
    TCCR2B = (1 << CS22) | (1 << CS21);    // prescaler = 256
}

void Sonarite::arreterSon()
{
    TCNT2 = 0;
    OCR2A = 0;
    TCCR2A = 0;
    TCCR2B = 0;
};

uint16_t Sonarite::convertirNote(uint8_t noteDonnee)
{
    switch (noteDonnee)
    {
    case 45:
        return 110; // A2
    case 46:
        return 116; // Ad2
    case 47:
        return 123; // B2
    case 48:
        return 130; // C3
    case 49:
        return 138; // Cd3
    case 50:
        return 146; // D3
    case 51:
        return 155; // Dd3
    case 52:
        return 164; // E3
    case 53:
        return 174; // F3
    case 54:
        return 184; // Fd3
    case 55:
        return 195; // G3
    case 56:
        return 207; // Gd3
    case 57:
        return 220; // A3
    case 58:
        return 233; // Ad3
    case 59:
        return 246; // B3
    case 60:
        return 261; // C4
    case 61:
        return 277; // Cd4
    case 62:
        return 293; // D4
    case 63:
        return 311; // Dd4
    case 64:
        return 329; // E4
    case 65:
        return 349; // F4
    case 66:
        return 369; // Fd4
    case 67:
        return 391; // G4
    case 68:
        return 415; // Gd4
    case 69:
        return 440; // A4
    case 70:
        return 466; // Ad4
    case 71:
        return 494; // B4
    case 72:
        return 523; // C5
    case 73:
        return 554; // Cd5
    case 74:
        return 587; // D5
    case 75:
        return 622; // Dd5
    case 76:
        return 659; // E5
    case 77:
        return 698; // F5
    case 78:
        return 739; // Fd5
    case 79:
        return 784; // G5
    case 80:
        return 831; // Gd5
    case 81:
        return 880; // A5
    }
}
