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

class Sonarite
{
public:
    uint16_t convertirNote(uint8_t noteDonnee)
    {
        static const std::unordered_map<uint8_t, uint16_t> noteMap = {
            {45, 110}, {46, 116}, {47, 123}, {48, 130}, {49, 138}, {50, 146}, {51, 155}, {52, 164}, {53, 174}, {54, 184}, {55, 195}, {56, 207}, {57, 220}, {58, 233}, {59, 246}, {60, 261}, {61, 277}, {62, 293}, {63, 311}, {64, 329}, {65, 349}, {66, 369}, {67, 391}, {68, 415}, {69, 440}, {70, 466}, {71, 494}, {72, 523}, {73, 554}, {74, 587}, {75, 622}, {76, 659}, {77, 698}, {78, 739}, {79, 784}, {80, 831}, {81, 880}};

        auto iter = noteMap.find(noteDonnee);
        if (iter != noteMap.end())
        {
            return iter->second;
        }

        return 0;
    }
};