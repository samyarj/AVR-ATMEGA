#include "capteurs.h"

volatile uint16_t DistanceSensor::obtenirDistance(void)
{
    uint16_t resultat = 0;
    for (int i = 0; i < NbValeursPourMoyenne_; i++)
    {
        resultat += can_.lecture(2);
        resultat = resultat >> 2;
    }

    // calcule de la moyenne
    resultat = resultat / NbValeursPourMoyenne_;

    return resultat;
}
