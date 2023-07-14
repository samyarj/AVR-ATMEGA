#include "capteurs.h"


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





