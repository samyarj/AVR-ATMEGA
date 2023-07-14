#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "controlPort.h
#include "memoire_24.h"

executionInitialiser::executionInitialiser(){

}

executionInitialiser::lectureMemoire(){   
    Memoire24CXXX memoire;

  //--------------------------TAILLE DU FICHIER----------------------------------------

    memoire.lecture(Adresse, &commande);
    Adresse++;
    tailleDuFichier = commande;

    memoire.lecture(Adresse, &commande);
    Adresse++;

    tailleDuFichier = (tailleDuFichier << 8) + commande;


    while (commande != Debut)
    {
    memoire.lecture(Adresse, &commande);
    Adresse++;

    memoire.lecture(Adresse, &donnee);
    Adresse++;
    }


    while (Adresse < tailleDuFichier)
    {
    memoire.lecture(Adresse, &commande);
    Adresse++;

    memoire.lecture(Adresse, &donnee);
    Adresse++;

    }
}
executionInitialiser::debutBoucle(){
    AdresseDeRetourPourBoucle = Adresse;
    CompteurPourBoucle = donnee; // le compteur sera initialié au nombre de fois que l'on veut refaire la loop

}
executionInitialiser::finBoucle(){
    if (CompteurPourBoucle > 0)
    {

        Adresse = AdresseDeRetourPourBoucle;
        CompteurPourBoucle--;
    }

}
executionInitialiser::finFin(){
    Adresse = tailleDuFichier; // va faire en sorte que l'on se retrouve a la derniere adresse du fichier ce qui va nous faire sortir de la boucle

    // eteindre nos trucs si ya des trucs encore allumé
}
uint8_t executionInitialiser::
{
	return donnee;
}

