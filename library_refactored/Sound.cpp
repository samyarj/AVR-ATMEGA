#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "Sound.h"
#include <unordered_map>

Sound::Sound()
{
    activateOutMode();
    togglePort(_mode00);
    // setPort(&DDRD, 6, 3);
    // setPort(&PORTD, 6, 0);
}

Sound::~Sound()
{
    activateInMode();
    togglePort(_mode00);
    // setPort(&DDRD, 6, 0);
    // setPort(&PORTD, 6, 0);
}

void Sound::startSound(uint16_t noteFrequency)
{
    TCNT2 = 0;
    OCR2A = (CPU_PRESCALER_ / (noteFrequency)) - 1;
    TCCR2A = (1 << COM2A0) | (1 << WGM21); // compare match,  Mode CTC
    TCCR2B = (1 << CS22) | (1 << CS21);    // prescaler = 256
}

void Sound::stopSound()
{
    TCNT2 = 0;
    OCR2A = 0;
    TCCR2A = 0;
    TCCR2B = 0;
};

uint16_t Sound::convertNote(uint8_t givenNote)
{
    static const std::unordered_map<uint8_t, uint16_t> noteMap = 
    {
        {45, 110}, {46, 116}, {47, 123}, {48, 130}, {49, 138}, 
        {50, 146}, {51, 155}, {52, 164}, {53, 174}, {54, 184}, 
        {55, 195}, {56, 207}, {57, 220}, {58, 233}, {59, 246}, 
        {60, 261}, {61, 277}, {62, 293}, {63, 311}, {64, 329}, 
        {65, 349}, {66, 369}, {67, 391}, {68, 415}, {69, 440}, 
        {70, 466}, {71, 494}, {72, 523}, {73, 554}, {74, 587}, 
        {75, 622}, {76, 659}, {77, 698}, {78, 739}, {79, 784}, 
        {80, 831}, {81, 880}
    };

    auto iter = noteMap.find(givenNote);
    if (iter != noteMap.end())
    {
        return iter->second;
    }

    return 0;
}
