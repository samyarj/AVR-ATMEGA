#include "transmission.h"

void TransmissionSVG::crc32(uint8_t a)
{
    uint8_t i;
    crc ^= a;
    for (i = 0; i < 8; ++i)
    {
        if (crc & 1)
            crc = (crc >> 1) ^ 0xEDB88320;
        else
            crc = (crc >> 1);
    }
}

int TransmissionSVG::orientation(Point point1, Point point2, Point point3)
{
    int val = (point2.y - point1.y) * (point3.x - point2.x) -
              (point2.x - point1.x) * (point3.y - point2.y);
    if (val == 0)
        return 0; // Les points sont colinéaires
    else if (val > 0)
        return 1; // Sens horaire
    else
        return 2; // Sens anti-horaire
}

void TransmissionSVG::lirePositionPoteau()
{

    for (int i = 0; i < 32; i++)
    {
        memoire.lecture(i, &poteaux[i]);
        _delay_ms(5);
    }
}

void TransmissionSVG::transmettreImageInitiale()
{
    char svgInitiale[] = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%\" height=\"100%\" viewBox=\"0 0 1152 576\">"
                         "<rect x=\"96\" y=\"48\" width=\"960\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/> <text x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\"> Section 03 -- Equipe 6163 -- Pac Bot </text>";
    uint16_t nCaracteresImageInitiale = strlen(svgInitiale);
    communication.transmettreUART(DEBUT_TXT);
    for (uint16_t i = 0; i < nCaracteresImageInitiale; i++)
    {
        communication.transmettreUART(svgInitiale[i]);
        crc32(svgInitiale[i]);
    }
}

void TransmissionSVG::determinerNPoteau()
{
    for (int i = 0; i < 32; i++)
    {
        if (poteaux[i] == 1)
        {
            nPoteaux++;
        }
    }
}

void TransmissionSVG::determinerPoteauxPoint(Point *positionsPoteauxXY)
{
    int compteur = 0;
    for (int i = 0; i < 32; i++)
    {
        if (poteaux[i] == 1)
        {
            positionsPoteauxXY[compteur].x = i / 4;
            positionsPoteauxXY[compteur].y = i - 4 * positionsPoteauxXY[compteur].x;
            compteur++;
        }
    }
}

void TransmissionSVG::enveloppeConvexe(Point positionsPoteauxXY[], Point *enveloppe)
{
    // Cas de base : s'il y a moins de 3 points, alors tous les points sont sur l'enveloppe convexe
    if (nPoteaux < 3)
    {
        for (int i = 0; i < nPoteaux; i++)
        {
            enveloppe[i] = positionsPoteauxXY[i];
        }
        tailleEnveloppe = nPoteaux;
    }
    else
    {
        // Trouver le point le plus à gauche
        int pointGauche = 0;
        for (int i = 1; i < nPoteaux; i++)
        {
            if (positionsPoteauxXY[i].x < positionsPoteauxXY[pointGauche].x)
            {
                pointGauche = i;
            }
        }

        int pointCourant = pointGauche; // Point courant sur l'enveloppe convexe
        int prochainPoint;              // Prochain point sur l'enveloppe convexe

        do
        {
            // Ajouter le point courant à l'enveloppe convexe
            enveloppe[tailleEnveloppe] = positionsPoteauxXY[pointCourant];
            tailleEnveloppe++;
            // Trouver le prochain point sur l'enveloppe convexe
            prochainPoint = (pointCourant + 1) % nPoteaux;
            for (int i = 0; i < nPoteaux; i++)
            {
                // Si le point i est plus à gauche que le point courant par rapport au point courant et au prochain point
                if (orientation(positionsPoteauxXY[pointCourant], positionsPoteauxXY[i], positionsPoteauxXY[prochainPoint]) == 2)
                {
                    prochainPoint = i;
                }
            }
            pointCourant = prochainPoint;      // Mettre à jour le point courant pour la prochaine itération
        } while (pointCourant != pointGauche); // Arrêter lorsque nous revenons au point de départ
    }
}

void TransmissionSVG::calculerAire(Point enveloppe[])
{
    for (int i = 0; i < tailleEnveloppe; i++)
    {
        aire += (((enveloppe[i].x) * (enveloppe[(i + 1) % tailleEnveloppe].y)) - ((enveloppe[(i + 1) % tailleEnveloppe].x) * enveloppe[i].y));
    }
    aire *= 121; // 11 au carre
    aire /= 2;
    if (aire < 0)
        aire *= -1;
}

void TransmissionSVG::determinerHullSVG(Point *hullSVG, Point *enveloppe)
{
    for (int i = 0; i < tailleEnveloppe; i++)
    {
        hullSVG[i].x = svgpoints[4 * enveloppe[i].x + enveloppe[i].y][0];
        hullSVG[i].y = svgpoints[4 * enveloppe[i].x + enveloppe[i].y][1];
    }
}

void TransmissionSVG::transmettreAire()
{
    uint16_t nCaracteresAire;
    char airePolygone[100];
    nCaracteresAire = sprintf(airePolygone, "<text x=\"96\" y=\"553\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">AIRE: %d pouces carres</text>", aire);
    for (uint16_t i = 0; i < nCaracteresAire; i++)
    {
        communication.transmettreUART(airePolygone[i]);
        crc32(airePolygone[i]);
    }
}

void TransmissionSVG::transmettrePolygoneMilieu(Point *hullSVG)
{
    char milieuPolygone[100];
    milieuPolygone[0] = '\0';

    for (uint8_t i = 0; i < tailleEnveloppe; i++)
    {
        char chaine[20];
        sprintf(chaine, "%d,%d ", hullSVG[i].x, hullSVG[i].y);
        strcat(milieuPolygone, chaine);
    }

    char airePolygone[200];
    sprintf(airePolygone, "<polygon points=\"%s\" width=\"770\" height=\"10\" stroke=\"black\" stroke-width=\"2\" fill=\"green\" />", milieuPolygone);

    communication.transmettreMessage(airePolygone);
    uint16_t nCar = strlen(airePolygone);
    for (uint16_t i = 0; i < nCar; i++)
    {
        crc32(airePolygone[i]);
    }
}

void TransmissionSVG::determinerPositionPoints()
{

    for (uint8_t i = 0; i < 32; i++)
    {
        uint8_t nCaracteres;
        char buffer[100];
        if ((i == 0) && (poteaux[i] == 0))
        {
            nCaracteres = sprintf(buffer,
                                  "<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" stroke=\"red\" stroke-width=\"1\" fill=\"red\"/>",
                                  svgpoints[i][0], svgpoints[i][1]);
        }
        else if ((poteaux[i] == 1))
        {
            nCaracteres = sprintf(buffer, "<circle cx=\"%d\" cy=\"%d\" r=\"10\" stroke=\"black\" stroke-width=\"1\" fill=\"grey\" />",
                                  svgpoints[i][0], svgpoints[i][1]);
        }
        else
        {
            nCaracteres = sprintf(buffer, "<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>",
                                  svgpoints[i][0], svgpoints[i][1]);
        }
        for (uint16_t i = 0; i < nCaracteres; i++)
        {
            communication.transmettreUART(buffer[i]);
            crc32(buffer[i]);
        }
    }
}

void TransmissionSVG::trasmettreImageFinale()
{
    char svgFin[] = "</svg>";
    uint8_t nCaracteresSvgFin = strlen(svgFin);
    for (uint8_t i = 0; i < nCaracteresSvgFin; i++)
    {
        communication.transmettreUART(svgFin[i]);
        crc32(svgFin[i]);
    }
    communication.transmettreUART(FIN_TXT);
}

void TransmissionSVG::envoyerSommeControle()
{
    char buffer[9];
    crc = ~crc;
    uint16_t msbCrc = crc >> 16;
    uint16_t lsbCrc = crc;
    uint8_t nCaracteres = sprintf(buffer, "%x%x", msbCrc, lsbCrc);
    for (uint8_t i = 0; i < nCaracteres; i++)
    {
        communication.transmettreUART(buffer[i]);
    }
}
