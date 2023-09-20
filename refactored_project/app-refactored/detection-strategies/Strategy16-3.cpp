#include "Strategy.h"


void Strategy16X3Y::execute(Deplacement& deplacement) override 
{
    _delay_ms(500);
    deplacement.tournerDroite90();
    deplacement.changerAngle(-90);
    _delay_ms(500);
    deplacement.avancerVersPoto();
    for (uint8_t i = 0; i < 4; i++)
    {
      _delay_ms(500);
      deplacement.avancerVersPotoD();
      if (deplacement.obtenirResultat() > 110)
      {
        return;
      }
    }
    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    return;
}
