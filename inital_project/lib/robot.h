#ifndef ROBOT_H
#define ROBOT_H
#include "lumiere.h"
#include "MinuteriePwm.h"
#include "sonarite.h"

class Robot
{
public:
    Robot();
    ~Robot();
    void attendre(uint16_t delaiVoulu);
    void allumerDEL(uint8_t couleur);
    void eteindreDEL();
    void sonner(uint8_t noteDonnee);
    void arreterDeSonner();
    void arreterMoteur();
    void avancer(uint16_t vitesse);
    void reculer(uint16_t vitesse);
    void tournerGauche90();
    void tournerDroite90();
    void tournerGauche45();
    void tournerDroite45();

private:
    Lumiere lumiere;
    MinuteriePwm minuterie0;
    Sonarite son;
};
#endif
