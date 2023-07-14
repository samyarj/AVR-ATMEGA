#include "robot.h"

Robot::Robot()
{
    // Initialisation des entrees/sorties
    lumiere.setPort(&DDRA, 0, 3); // témoin lumineux au port A
    minuterie0.setPort(&DDRB, 2, 3);
    minuterie0.setPort(&DDRB, 4, 3);
}

Robot::~Robot()
{
    lumiere.setPort(&DDRA, 0, 0); // témoin lumineux au port A
    minuterie0.setPort(&DDRB, 2, 0);
    minuterie0.setPort(&DDRB, 4, 0);
}

void Robot::attendre(uint16_t delaiVoulu)
{
    for (uint16_t i = 0; i < delaiVoulu; i++)
        _delay_ms(50);
}

void Robot::allumerDEL(uint8_t couleur)
{
    if (couleur == 1)
        lumiere.changerCouleur(lumiere.vert());
    else if (couleur == 2)
        lumiere.changerCouleur(lumiere.rouge());
}

void Robot::eteindreDEL()
{
    lumiere.changerCouleur(lumiere.eteint());
}

void Robot::sonner(uint8_t noteDonnee)
{
    uint16_t frequence_note = son.convertirNote(noteDonnee);
    son.commencerSon(frequence_note);
}

void Robot::arreterDeSonner()
{
    son.arreterSon();
}

void Robot::arreterMoteur()
{
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
}

void Robot::avancer(uint16_t vitesse)
{
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), vitesse, vitesse);
}

void Robot::reculer(uint16_t vitesse)
{
    minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.reculer(), vitesse, vitesse);
}

void Robot::tournerGauche90()
{
    minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 255, 255);
    _delay_ms(50);
    minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 95, 95);
    _delay_ms(800);
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
    _delay_ms(700);
}

void Robot::tournerDroite90()
{
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 255, 255);
    _delay_ms(100);
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 95, 95);
    _delay_ms(800);
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
    _delay_ms(700);
}

void Robot::tournerGauche45()
{
    minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 125, 125);
    minuterie0.delai(765, minuterie0.facteurMs()); // changer valeur pour trouver durée exacte
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
}

void Robot::tournerDroite45()
{
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 125, 125);
    minuterie0.delai(755, minuterie0.facteurMs()); // changer valeur pour trouver durée exacte
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
}
