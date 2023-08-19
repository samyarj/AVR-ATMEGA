#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "MinuteriePwm.h"

uint8_t MinuteriePwm::genererMaskPWM(uint8_t bitVoulu, uint8_t masque)
{
    // Mask pour eteindre (PORTX &= 11100011). A utiliser avant de changer de couleur.
    if (masque == _masque000)
        return (~((1 << bitVoulu) | (1 << (bitVoulu + 1)) | (1 << (bitVoulu + 2))));
    // Mask pour rouge (PORTX |= XXX001XX)
    else if (masque == _masque001)
        return (1 << bitVoulu);
    // Mask pour vert (PORTX |= XXX011XX)
    else if (masque == _masque011)
        return ((1 << bitVoulu) | (1 << (bitVoulu + 1)));
    // Mask pour mode sortie (PORTX |= XXX101X)
    else
        return ((1 << bitVoulu) | (1 << (bitVoulu + 2)));
}

void MinuteriePwm::selectionnerFrequencePwmMoteur(Frequence frequence)
{
    switch (frequence)
    {
    case Frequence::f15HZ:
        TCCR0B &= genererMaskPWM(CS10, _masque000);
        TCCR0B |= genererMaskPWM(CS10, _masque101);
        break;

    case Frequence::f61HZ:
        TCCR0B &= genererMaskPWM(CS10, _masque000);
        TCCR0B |= genererMaskPWM(CS12, _masque001);
        break;

    case Frequence::f245HZ:
        TCCR0B &= genererMaskPWM(CS10, _masque000);
        TCCR0B |= genererMaskPWM(CS10, _masque011);
        break;

    case Frequence::f1961HZ:
        TCCR0B &= genererMaskPWM(CS10, _masque000);
        TCCR0B |= genererMaskPWM(CS11, _masque001);
        break;

    case Frequence::f15686HZ:
        TCCR0B &= genererMaskPWM(CS10, _masque000);
        TCCR0B |= genererMaskPWM(CS10, _masque001);
        break;
    }
}

void MinuteriePwm::ajustementPwmMoteur(uint8_t pourcentageRoueGauche, uint8_t pourcentageRoueDroite, Frequence frequence)
{
    OCR0A = pourcentageRoueGauche; //* _TOP / 100; // fonctionne si le pourcentage excède 100%, mais le réechelonne entre 0 et 255
    OCR0B = pourcentageRoueDroite; //* _TOP / 100;

    // division d'horloge par 8 - implique une fréquence de PWM fixe
    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);

    selectionnerFrequencePwmMoteur(frequence);
}

void MinuteriePwm::controlerMoteur(uint8_t directionGauche, uint8_t directionDroite, uint8_t pourcentageRoueGauche, uint8_t pourcentageRoueDroite)
{
    setPort(_PORT_MOTEUR, _BIT_MOTEUR - 1, directionGauche);
    setPort(_PORT_MOTEUR, _BIT_MOTEUR + 2, directionDroite);
    ajustementPwmMoteur(pourcentageRoueGauche, pourcentageRoueDroite, Frequence::f245HZ);
}
