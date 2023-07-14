#include "capteurs.h"



/*float DistanceSensor::conversionBitVoltage(uint16_t resultat) {
    if (10 < resultat < 25)
        return 0.4;
    else if (26 < resultat < 40)
        return 0.5

    else if (41 < resultat < 60) // A tester je suis allé au pif
        return 0.7;

    else if (61 < resultat < 70) // en plus ya surmeent un probleme de code ici faudra le regler
        return 0.9;
    
    else if (71 < resultat < 80)
        return 1.1;

    else if (81 < resultat < 90)
        return 1.3;

    else if (91 < resultat < 100)
        return 1.6;

    else if (101 < resultat < 110)
        return 1.9;
    
    else if (111 < resultat < 120)
        return 2.3;

    else if (121 < resultat < 129)
        return 2.6;

    else if (130 < resultat < 135)
        return 2.9;

    else if (136 < resultat < 142)
        return 3.0;

    else
        return 3.2;
    }

*/

volatile uint16_t DistanceSensor::obtenirDistance( void) {
uint16_t resultat = 0;
for (int i = 0; i < NbValeursPourMoyenne_; i++) {
resultat += can_.lecture(2); 
resultat = resultat >> 2;
//_delay_ms(DelaisEntreLecture_);
}
//calcule de la moyenne
resultat = resultat / NbValeursPourMoyenne_;

// calcul passant du voltage a la longeur en cm
/*float voltage = conversionBitVoltage(resultat);
resultat = (1/ ((voltage - a)/b)) *100;
*/

return resultat;
}





