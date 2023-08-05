#include "Strategy.h"


void Strategy0X0YUP::execute(Deplacement& deplacement) override
{
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
        return;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
        return;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
        return;
    }
    if (deplacement.obtenirResultat() < 110)
    {
        detecte = false;
    }
};
