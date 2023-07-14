#ifndef CAPTEURS_H
#define CAPTEURS_H
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "can.h"






// je propose que l'on utilise cette classe avec un compteur. Donc a chaque fois que l'on atteint la valeur du compteur de temps (interruption) 
    // on va alors utiliser la methode obtenirDistance pour avoir un moyenne aproximative de la distance. Ensuite en fonction de cette derniere 
    // on decide de faire avancer ou tourner le robot.
class DistanceSensor {
public:
    DistanceSensor(can& can) : can_(can) {}

// Constantes pour obtenir la distance en fonction du voltage

//     Pour obtenir les valeurs a et b, vous avez besoin de deux points de mesure correspondant à une distance connue et la valeur lue par le capteur à cette distance. Vous pouvez utiliser une règle pour mesurer la distance précise entre le capteur et l'objet et noter la valeur lue par le capteur correspondante.

// Une fois que vous avez ces deux points de mesure, vous pouvez utiliser la formule de la droite pour trouver les valeurs a et b. La formule de la droite est la suivante: y = ax + b, où y représente la distance mesurée en centimètres et x représente la valeur lue par le capteur.

// Pour trouver la valeur de a, vous pouvez utiliser la formule suivante: a = (y2 - y1) / (x2 - x1), où y2 et y1 sont les distances mesurées pour les deux points de mesure, et x2 et x1 sont les valeurs lues par le capteur correspondantes.

// Pour trouver la valeur de b, vous pouvez utiliser la formule suivante: b = y1 - (a * x1), où y1 est la distance mesurée pour le premier point de mesure, et x1 est la valeur lue par le capteur correspondante.

// Une fois que vous avez trouvé les valeurs de a et b, vous pouvez utiliser la formule y = ax + b pour convertir les valeurs lues par le capteur en distances en centimètres.
    const uint16_t a = 0; // a determiner
    const uint16_t b = 0;



    volatile uint16_t obtenirDistance(void);
    //float conversionBitVoltage(uint16_t resultat);

private:
    can& can_;
    const uint8_t DelaisEntreLecture_ = 30;
    const uint8_t NbValeursPourMoyenne_ = 60;
};
#endif