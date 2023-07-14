/* 
Description du programme:
Dans cet algorithme, le robot a pour but de détecter plusieurs poteaux sur une table 4x8 (distance de 11 pouces entre chaque points
horizontaux/verticaux) et de transmettre une image svg de tous les points auxquels les poteaux ont été détectés à un script python
de tranmission d'une image svg. Avant la détection, le robot devra être placé au point rouge et sa position vers le haut ou vers la
droite influencera les mouvements du robot. Le bouton blanc ou le bouton interrupteur doit être pressé pour choisir la direction.
Pendant la détection, le robot devra se déplacer vers un poteau, s'arrêter à une certaine distance et faire clignoter la DEL de 
couleur ambre.  À la fin de la détection, la DEL sera de couleur rouge. Lors de la transmission des données du robot vers l'ordinateur
portable, la LED clignotera en vert puis transmettra l'image d'un polygone convexe avec l'aire du polygone et le nom de l'équipe.

Identification matérielles (Broches I/O):
PORTA0-A1: DEL
PORTA4: capteurs
PORTA Vcc-GND: alimentation capteurs
PORTB2-B3: roue gauche
PORTB4-B5: roue droite
PORT C0-C1: Signal du bouton blanc
PORT D6-D7: Sonare
PORTD Vcc-GND: alimentation bouton blanc
*/

#define F_CPU 8000000UL
#include "deplacement.h"
#include "interupteurs.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include "communicationRS232.h"
#include "transmission.h"

enum Case
{
  POS0X0YHAUT,
  POS0X0YDROITE,
  POS16X0YHAUT,
  POS7X0YHAUT,
  POS0X12YHAUT,
  POS16X12YHAUT,
  POS7X12YHAUT,
  POS0X3YHAUT,
  POS16X3YHAUT,
  POS7X3YHAUT,
};

const Case CASE_INITIAL = Case::POS7X3YHAUT;
Deplacement deplacement;
Robot robot;
Interupt interrupteur;
BoutonBlanc bouton;

volatile bool attendre = true;
volatile bool mode = true;

volatile bool direction = true;
volatile bool haut = true;
volatile bool prochainePosition = true;

bool detecte = true;

volatile Case etat;

ISR(INT0_vect)
{
  _delay_ms(30);
  if (interrupteur.verifierPIN() && attendre)
    attendre = false;
  else if (interrupteur.verifierPIN() && direction)
  {
    direction = false;
  }
  else if (interrupteur.verifierPIN())
    prochainePosition = false;
  EIFR |= (1 << INTF0);
}

ISR(PCINT2_vect)
{
  _delay_ms(30);
  if (bouton.verifierPIN() && attendre)
  {
    attendre = false;
    mode = false;
  }
  else if (bouton.verifierPIN() && direction)
  {
    direction = false;
    haut = false;
  }
  PCIFR |= (1 << PCIF2);
}

// pour clignoter la DEL
void timer1_init()
{
  TCCR1B |= (1 << WGM12);              // mode CTC
  TIMSK1 |= (1 << OCIE1A);             // Enable compare match interrupt
  OCR1A = 390;                         // comparer a chaque 1 second interrupt at 16MHz clock
  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler = 1024
}
volatile int compteur = 0;

ISR(TIMER1_COMPA_vect)
{
  compteur++;
  if (compteur % 2 == 0)
    robot.allumerDEL(1);
  else
    robot.eteindreDEL();
}
void timer1_arret()
{
  TIMSK1 &= ~(1 << OCIE1A); // disable compare match interrupt// prescaler = 1024
}

Case choisirCase(uint8_t x, uint8_t y) // penser à essayer const uint8_t&
{
  if (x == 0)
  {
    if (y == 0)
    {
      if (haut)
        return Case::POS0X0YHAUT;
      else
      {
        deplacement.changerAngle(-90);
        return Case::POS0X0YDROITE;
      }
    }
    else if (y < 3)
      return Case::POS0X12YHAUT;
    else
      return Case::POS0X3YHAUT;
  }
  else if (x < 7)
  {
    if (y == 0)
      return Case::POS16X0YHAUT;
    else if (y < 3)
      return Case::POS16X12YHAUT;
    else
      return Case::POS16X3YHAUT;
  }
  else
  {
    if (y == 0)
      return Case::POS7X0YHAUT;
    else if (y < 3)
      return Case::POS7X12YHAUT;
    else
      return Case::POS7X3YHAUT;
  }
}

void algorithme(Case Case)
{
  switch (Case)
  {
  case POS0X0YHAUT:
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }
    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS0X0YDROITE: // Robot pointe vers la droite et est situé a la positionY et positionX 0 :
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS16X0YHAUT:
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.tournerDroite90();
    deplacement.changerAngle(90);

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS7X0YHAUT:
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS0X12YHAUT:
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoD();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS16X12YHAUT:
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    for (uint8_t i = 0; i < 8; i++)
    {
      _delay_ms(500);
      deplacement.avancerVersPotoD();
      if (deplacement.obtenirResultat() > 110)
      {
        break;
      }
    }
    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS7X12YHAUT:
    _delay_ms(500);
    deplacement.avancerVersPoto();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    _delay_ms(500);
    deplacement.avancerVersPotoG();
    if (deplacement.obtenirResultat() > 110)
    {
      break;
    }

    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS0X3YHAUT:

    _delay_ms(500);
    deplacement.tournerDroite90();
    deplacement.changerAngle(-90);
    _delay_ms(500);
    deplacement.avancerVersPoto();
    for (uint8_t i = 0; i < 2; i++)
    {
      _delay_ms(500);
      deplacement.avancerVersPotoD();
      if (deplacement.obtenirResultat() > 110)
      {
        break;
      }
    }

    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS16X3YHAUT:
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
        break;
      }
    }
    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;

  case POS7X3YHAUT:
    _delay_ms(500);
    deplacement.tournerGauche90();
    deplacement.changerAngle(90);
    for (uint8_t i = 0; i < 2; i++)
    {
      _delay_ms(500);
      deplacement.avancerVersPotoG();
      if (deplacement.obtenirResultat() > 110)
      {
        break;
      }
    }

    if (deplacement.obtenirResultat() < 110)
    {
      detecte = false;
    }
    break;
  }
}

void choregraphie()
{
  prochainePosition = true;
  deplacement.reinitialiserAngle();
  cli();
  Case caseAlgo = choisirCase(deplacement.getX(), deplacement.getY());
  algorithme(caseAlgo);

  // à la fin de la choregraphie, le robot attend qu'on
  // appuie sur interrupt pour sortir de la fonction et
  // reprendre la choregraphie
  sei();
  if (detecte)
  {
    for (int i = 0; i < 3; i++)
    {
      robot.sonner(71 + 2 * i);
      _delay_ms(300);
      robot.arreterDeSonner();
      _delay_ms(300);
    }
  }

  while (prochainePosition && detecte)
  {
    for (int i = 0; i < 1000; i++)
    {
      robot.allumerDEL(2);
      _delay_us(50);
      robot.allumerDEL(1);
      _delay_us(200);
    }
    robot.eteindreDEL();
    _delay_ms(250);
  }
  robot.eteindreDEL();
}

void positionHaut()
{
  robot.allumerDEL(1);
  _delay_ms(2000);
  robot.eteindreDEL();
  deplacement.reinitialiserAngle();
}

void positionDroite()
{
  robot.allumerDEL(2);
  _delay_ms(2000);
  robot.eteindreDEL();
  deplacement.reinitialiserAngle();
}

void modeDetection()
{
  do
  {
    robot.allumerDEL(2);
    _delay_us(30);
    robot.allumerDEL(1);
    _delay_us(150);
  } while (direction);
  if (haut)
    positionHaut();
  else
    positionDroite();
}

void transmettreDonnee()
{
  timer1_init();
  TransmissionSVG transmission;
  communicationRS232 communication;
  transmission.lirePositionPoteau();
  transmission.transmettreImageInitiale(); // rectangle + nom d'equipe
  transmission.determinerNPoteau();

  Point positionsPoteauxXY[transmission.getnPoteaux()];
  transmission.determinerPoteauxPoint(positionsPoteauxXY);

  Point enveloppe[transmission.getnPoteaux()];
  transmission.enveloppeConvexe(positionsPoteauxXY, enveloppe);

  transmission.calculerAire(enveloppe);

  Point hullSVG[transmission.getTailleEnveloppe()];
  transmission.determinerHullSVG(hullSVG, enveloppe);

  transmission.transmettreAire();

  transmission.transmettrePolygoneMilieu(hullSVG);

  transmission.determinerPositionPoints();

  transmission.trasmettreImageFinale();
  transmission.envoyerSommeControle();

  communication.transmettreUART(transmission.getFinTransmission());
  timer1_arret();
}

void modeTransmission()
{
  robot.allumerDEL(1);
  _delay_ms(2000);
  transmettreDonnee();
}

int main()
{
  interrupteur.initialisationInterrupt();
  bouton.initialisationInterrupt();
  while (attendre)
    ;
  if (mode)
  {
    modeDetection();
    while (detecte)
    {
      choregraphie();
      // on sort de la loop uniquement lorsque le robot
      // n'a rien détecté (quand bool detecte = false
      //  pour indiquer que rien n'a été détecté)
    }
    deplacement.ecrireMemoire();
    robot.sonner(45);
    _delay_ms(2000);
    robot.arreterDeSonner();

    while (true)
    {
      // faire clignoter DEL en rouge à 2 Hz
      robot.allumerDEL(2);
      _delay_ms(250);
      robot.eteindreDEL();
      _delay_ms(250);
    };
  }
  else
  {
    modeTransmission();
    robot.eteindreDEL();
  }
  while (true)
    ;
  return 0;
}
