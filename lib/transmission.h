#include <avr/io.h>
#include <util/delay.h>
#include "lumiere.h"
#include <stdio.h>
#include "memoire_24.h"
#include "communicationRS232.h"
#include <string.h>
#include <stdio.h>
#include <util/crc16.h>
#include <math.h>

struct Point
{
    int x, y;
};

class TransmissionSVG
{
public:
    void lirePositionPoteau();
    void transmettreImageInitiale();
    void determinerNPoteau();
    void determinerPoteauxPoint(Point *positionsPoteauxXY);
    void enveloppeConvexe(Point positionsPoteauxXY[], Point *enveloppe);
    void calculerAire(Point enveloppe[]);
    void determinerHullSVG(Point *hullSVG, Point *enveloppe);
    void transmettreAire();
    void transmettrePolygoneMilieu(Point *hullSVG);
    void determinerPositionPoints();
    void trasmettreImageFinale();
    void envoyerSommeControle();
    uint8_t getnPoteaux() { return nPoteaux; }
    uint16_t getAire() { return aire; }
    int getTailleEnveloppe() { return tailleEnveloppe; }
    uint8_t getFinTransmission() { return FIN_TRANSMISSION; }

private:
    uint32_t crc = 0xffffffff;
    uint8_t DEBUT_TXT = 0x02;
    uint8_t FIN_TXT = 0x03;
    uint8_t FIN_TRANSMISSION = 0x04;
    const uint16_t svgpoints[32][2] = {{188, 450}, {188, 340}, {188, 230}, {188, 120}, {298, 450}, {298, 340}, {298, 230}, {298, 120}, {408, 450}, {408, 340}, {408, 230}, {408, 120}, {518, 450}, {518, 340}, {518, 230}, {518, 120}, {628, 450}, {628, 340}, {628, 230}, {628, 120}, {738, 450}, {738, 340}, {738, 230}, {738, 120}, {848, 450}, {848, 340}, {848, 230}, {848, 120}, {958, 450}, {958, 340}, {958, 230}, {958, 120}};
    communicationRS232 communication;
    Memoire24CXXX memoire;
    uint8_t poteaux[32];
    uint8_t nPoteaux = 0;
    uint16_t aire = 0;
    int tailleEnveloppe = 0;
    void crc32(uint8_t a);
    int orientation(Point point1, Point point2, Point point3);
};