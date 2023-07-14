#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "lumiere.h"

Lumiere::Lumiere()
{
}

void Lumiere::changerCouleur(uint8_t sortie)
{
  setPort(PORT_DEL, _BIT_DEL, sortie);
}

void Lumiere::changerCouleurDelai(uint8_t sortie, uint32_t delaiVoulu, uint32_t facteur)
{
  if (sortie == _AMBRE)
  {
    uint32_t iterations = (_FREQUENCE_DEL * delaiVoulu) / facteur;
    for (uint32_t i{0}; i < iterations; i++)
    {
      changerCouleur(_ROUGE);
      _delay_us(31);
      changerCouleur(_VERTE);
      _delay_us(73);
      _delay_us(73);
      _delay_us(73);
    }
  }
  else
  {
    changerCouleur(sortie);
    delai(delaiVoulu, facteur);
  }
}
