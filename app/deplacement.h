#include "memoire_24.h"
#include "minuterie.h"
#include "MinuteriePwm.h"
#include "debug.h"
#include "robot.h"
#include "can.h"
#include "memoire_24.h"

class Deplacement
{
public:
    uint16_t getResultat();
    uint16_t obtenirResultat() { return resultat; }
    void avancerVersPotoD();
    void avancerVersPoto();
    void avancerVersPotoG();
    void tournerGauche90();
    void tournerDroite90();
    void ajusterpositionEnFonctionDeDistance();
    void changerAngle(int angle);
    void updateposition();
    void reinitialiserAngle();
    uint8_t getX() { return x_; }
    uint8_t getY() { return y_; }
    void enregistrerPoteau();
    void ecrireMemoire();

private:
    Robot robot;
    can convert;
    MinuteriePwm minuterie0;
    Memoire24CXXX memoire;
    uint16_t resultat;
    uint16_t resultat0;
    uint16_t resultat1;
    int angle_ = 0;
    int x_ = 0;
    int y_ = 0;
    void Gauche10();
    void Gauche15();
    void Droite10();
    void Droite15();
    void Gauche45();
    void Droite45();
    void Droite5();
    void Gauche5();
    void mouvementXY(int x, int y);
    bool poteauxDetectes[32] = {};
};
