#include "deplacement.h"

uint16_t Deplacement::getResultat()
{
    resultat0 = 0;
    for (uint8_t i = 0; i < 10; i++)
    {
        resultat1 = convert.lecture(4);
        resultat1 >>= 2;
        resultat0 += resultat1;
    }
    resultat0 = resultat0 / 10;
    return resultat0;
};

void Deplacement::Gauche45()
{
    Deplacement::changerAngle(45); //// UPDATE
    for (int i = 0; i < 4; i++)
    {
        Deplacement::Gauche10();
        resultat = Deplacement::getResultat();
        if (resultat > 13)
            break;
    }
};

void Deplacement::Droite45()
{
    Deplacement::changerAngle(-45); // UPDATE
    for (int i = 0; i < 4; i++)
    {
        Deplacement::Droite10();
        resultat = Deplacement::getResultat();
        if (resultat > 13)
            break;
    }
};

void Deplacement::Gauche10()
{
    resultat = Deplacement::getResultat();
    if (resultat < 13)
    {
        minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 255, 255);
        _delay_ms(40);
    }
    minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 100, 95);
    for (uint16_t k = 0; k < 3; k++)
    {
        resultat = Deplacement::getResultat();

        if (resultat > 13)
        {
            break;
        }
        _delay_ms(100);
    }
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
    _delay_ms(700);
};

void Deplacement::Gauche5()
{
    resultat = Deplacement::getResultat();
    if (resultat < 13)
    {
        minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 255, 255);
        _delay_ms(40);
    }
    minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 100, 95);
    for (uint16_t k = 0; k < 2; k++)
    {
        resultat = Deplacement::getResultat();

        if (resultat > 13)
        {
            break;
        }
        _delay_ms(100);
    }
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
    _delay_ms(700);
}

void Deplacement::Droite5()
{
    resultat = Deplacement::getResultat();
    if (resultat < 13)
    {
        minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 255, 255);
        _delay_ms(40);
    }
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 100, 95);
    for (uint16_t k = 0; k < 2; k++)
    {
        resultat = Deplacement::getResultat();

        if (resultat > 13)
        {
            break;
        }
        _delay_ms(100);
    }

    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
    _delay_ms(700);
}

void Deplacement::Gauche15()
{
    for (int i = 0; i < 2; i++)
    {
        Deplacement::Gauche10();
        resultat = Deplacement::getResultat();
        if (resultat > 13)
            break;
    }
};

void Deplacement::Droite10()
{
    resultat = Deplacement::getResultat();
    if (resultat < 13)
    {
        minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 255, 255);
        _delay_ms(40);
    }
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 100, 95);
    for (uint16_t k = 0; k < 3; k++)
    {
        resultat = Deplacement::getResultat();

        if (resultat > 13)
        {
            break;
        }
        _delay_ms(100);
    }

    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
    _delay_ms(700);
};

void Deplacement::Droite15()
{
    for (int i = 0; i < 2; i++)
    {
        Deplacement::Droite10();
        resultat = Deplacement::getResultat();
        if (resultat > 13)
            break;
    }
};

void Deplacement::avancerVersPotoD()
{
    Deplacement::Droite45();
    Deplacement::Gauche15();
    Deplacement::Droite5();
    resultat = Deplacement::getResultat();
    if (resultat > 13)
    {
        Deplacement::ajusterpositionEnFonctionDeDistance(); //       à tester, mais pas nécessaire
        while (resultat < 115)
        {
            while (resultat < 115 && resultat > 18)
            {
                minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 255, 255);
                _delay_ms(50);
                minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 90, 80);
                _delay_ms(550);
                robot.arreterMoteur();
                _delay_ms(300);
                resultat = Deplacement::getResultat();
            }

            if (resultat < 18)
            {
                for (int i = 0; i < 2; i++)
                {
                    Deplacement::Droite10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
                for (int i = 0; i < 4; i++)
                {
                    Deplacement::Gauche10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
                for (int i = 0; i < 2; i++)
                {
                    Deplacement::Droite10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
            }
            resultat = Deplacement::getResultat();
        }
    }
};

void Deplacement::avancerVersPoto()
{
    resultat = Deplacement::getResultat();
    if (resultat > 13)
    {
        Deplacement::ajusterpositionEnFonctionDeDistance(); //       à tester, mais pas nécessaire
        // resultat = Deplacement::getResultat();
        while (resultat < 115)
        {
            while (resultat < 115 && resultat > 18)
            {
                minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 255, 255);
                _delay_ms(50);
                minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 90, 80);
                _delay_ms(550);
                robot.arreterMoteur();
                _delay_ms(300);
                resultat = Deplacement::getResultat();
            }

            if (resultat < 18)
            {
                for (int i = 0; i < 2; i++)
                {
                    Deplacement::Droite10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
                for (int i = 0; i < 4; i++)
                {
                    Deplacement::Gauche10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
                for (int i = 0; i < 2; i++)
                {
                    Deplacement::Droite10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
            }
            resultat = Deplacement::getResultat();
        }
    }
};

void Deplacement::avancerVersPotoG()
{
    Deplacement::Gauche45();
    Deplacement::Droite15();
    Deplacement::Gauche5();
    resultat = Deplacement::getResultat();
    if (resultat > 13)
    {
        Deplacement::ajusterpositionEnFonctionDeDistance(); //       à tester, mais pas nécessaire
        while (resultat < 115)
        {
            while (resultat < 115 && resultat > 18)
            {
                minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 255, 255);
                _delay_ms(50);
                minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 90, 80);
                _delay_ms(550);
                robot.arreterMoteur();
                _delay_ms(300);
                resultat = Deplacement::getResultat();
            }

            if (resultat < 18)
            {
                for (int i = 0; i < 2; i++)
                {
                    Deplacement::Droite10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
                for (int i = 0; i < 4; i++)
                {
                    Deplacement::Gauche10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
                for (int i = 0; i < 2; i++)
                {
                    Deplacement::Droite10();
                    resultat = Deplacement::getResultat();
                    if (resultat > 18)
                        break;
                }
            }
            resultat = Deplacement::getResultat();
        }
    }
}

void Deplacement::tournerGauche90()
{
    minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 255, 255);
    _delay_ms(85);
    minuterie0.controlerMoteur(minuterie0.reculer(), minuterie0.avancer(), 95, 95);
    _delay_ms(800);
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
    _delay_ms(700);
}

void Deplacement::tournerDroite90()
{
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 255, 255);
    _delay_ms(85);
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.reculer(), 95, 95);
    _delay_ms(800);
    minuterie0.controlerMoteur(minuterie0.avancer(), minuterie0.avancer(), 0, 0);
    _delay_ms(700);
}

void Deplacement::mouvementXY(int x, int y)
{
    this->x_ += x;
    this->y_ += y;
    if (x_ > 7)
        x_ = 7;
    if (y_ > 3)
        y_ = 3;
    if (x_ < 0)
        x_ = 0;
    if (y_ < 0)
        y_ = 0;
}

void Deplacement::changerAngle(int angle)
{
    if (angle_ >= 0 && angle_ <= 360) // angle doit etre entre 0 et 360
    {
        angle_ += angle;
        if (angle_ >= 360)
        {
            angle_ -= 360;
        }
        else if (angle_ < 0)
        {
            angle_ += 360;
        }
    }
}

void Deplacement::reinitialiserAngle()
{
    this->angle_ = 90;
}

void Deplacement::updateposition()
{
    if (angle_ == 90)
    {
        mouvementXY(0, 1);
        DEBUG_PRINT(("Incrémentation y"));
    }
    else if (angle_ == 45)
    {
        mouvementXY(1, 1);
        DEBUG_PRINT(("Incrémentation x et y"));
    }

    else if (angle_ == 0 || angle_ == 360)
    {
        mouvementXY(1, 0);
        DEBUG_PRINT(("Incrémentation x"));
    }

    else if (angle_ == 315)
    {
        mouvementXY(1, -1);
        DEBUG_PRINT(("Incrémentation x et decrementation y"));
    }

    else if (angle_ == 270)
    {
        mouvementXY(0, -1);
        DEBUG_PRINT(("Décrémentation y"));
    }

    else if (angle_ == 225)
    {
        mouvementXY(-1, -1);
        DEBUG_PRINT(("Décrémentation x et y"));
    }

    else if (angle_ == 180)
    {
        mouvementXY(-1, 0);
        DEBUG_PRINT(("Décrémentation x"));
    }

    else if (angle_ == 135)
    {
        mouvementXY(-1, 1);
        DEBUG_PRINT(("Décrémentation x et incrémentation y"));
    }
}

void Deplacement::ajusterpositionEnFonctionDeDistance()
{
    resultat = Deplacement::getResultat();
    if (resultat > 45)
    {
        Deplacement::updateposition();
    }
    else if (resultat < 45)
    {
        Deplacement::updateposition();
        Deplacement::updateposition();
    }
    Deplacement::enregistrerPoteau();
}

void Deplacement::enregistrerPoteau()
{
    poteauxDetectes[4 * x_ + (y_)] = true;
}

void Deplacement::ecrireMemoire()
{
    for (uint16_t i = 0; i < 32; i++)
    {
        if (poteauxDetectes[i])
        {
            memoire.ecriture(i, 1);
            _delay_ms(5);
        }
        else
        {
            memoire.ecriture(i, 0);
            _delay_ms(5);
        }
    }
}
