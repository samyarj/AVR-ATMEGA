#include "strategy.h"

void Strategy0X0YRight::execute(Deplacement &deplacement) 
{
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
        return;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
        return;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
        return;
    }

    if (deplacement.obtenirResultat() < 110)
    {
        detecte = false;
    }

}
