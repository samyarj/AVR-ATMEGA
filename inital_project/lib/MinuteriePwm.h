#ifndef MINUTERIEPWM_H
#define MINUTERIEPWM_H
#include "controlPort.h"
#include "frequencePwm.h"

class MinuteriePwm : public ControlPort
{
public:
   MinuteriePwm() = default;
   ~MinuteriePwm() = default;

   uint8_t genererMaskPWM(uint8_t bitVoulu, uint8_t masque);
   void selectionnerFrequencePwmMoteur(Frequence frequence);
   void ajustementPwmMoteur(uint8_t pourcentageRoueGauche, uint8_t pourcentageRoueDroite, Frequence frequence);
   void controlerMoteur(uint8_t directionGauche, uint8_t directionDroite, uint8_t pourcentageRoueGauche, uint8_t pourcentageRoueDroite);
   uint8_t avancer() { return _avancer; };
   uint8_t reculer() { return _reculer; };

private:
   uint16_t _TOP = 0xFF;
   uint8_t _masque000 = 0;
   uint8_t _masque001 = 1;
   uint8_t _masque011 = 2;
   uint8_t _masque101 = 3;
   uint8_t _avancer = 0;
   uint8_t _reculer = 1;
   volatile uint8_t *_PORT_MOTEUR = &PORTB;
   uint8_t _BIT_MOTEUR = 3;
};

#endif