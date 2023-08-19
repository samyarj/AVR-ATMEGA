#ifndef MEMOIRE_24_H
#define MEMOIRE_24_H

#include <avr/io.h>
#include <util/twi.h>


// A class to control the 24CXXX memory
class Memoire24CXXX
{
public:
   Memoire24CXXX();
   ~Memoire24CXXX();
   void init();
   static uint8_t choisir_banc(const uint8_t banc);
   uint8_t lecture(const uint16_t adresse, uint8_t *donnee);
   uint8_t lecture(const uint16_t adresse, uint8_t *donnee,
                   const uint8_t longueur);
   uint8_t ecriture(const uint16_t adresse, const uint8_t donnee);
   uint8_t ecriture(const uint16_t adresse, uint8_t *donnee,
                    const uint8_t longueur);

private:
   uint8_t ecrire_page(const uint16_t adresse, uint8_t *donnee,
                       const uint8_t longueur);

private:
   static uint8_t m_adresse_peripherique;
   const uint8_t PAGE_SIZE;
};

#endif /* MEMOIRE_24_H */
