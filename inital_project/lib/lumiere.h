#ifndef LUMIERE_H
#define LUMIERE_H
#include <avr/io.h>
#include <util/delay.h>
#include "controlPort.h"

class Lumiere : public ControlPort
{
public:
  Lumiere();
  ~Lumiere() = default;

  uint8_t eteint() { return _ETEINT; };
  uint8_t rouge() { return _ROUGE; };
  uint8_t vert() { return _VERTE; };
  uint8_t ambre() { return _AMBRE; };
  void changerCouleurDelai(uint8_t sortie, uint32_t delaiVoulu, uint32_t facteur);
  void changerCouleur(uint8_t sortie);

private:
  uint8_t _ETEINT = 0;
  uint8_t _ROUGE = 1;
  uint8_t _VERTE = 2;
  uint8_t _AMBRE = 3;

  uint8_t _BIT_DEL = 0;
  volatile uint8_t *PORT_DEL = &PORTA;
  uint32_t _FREQUENCE_DEL = 4000;
};
#endif