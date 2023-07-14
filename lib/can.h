#ifndef CAN_H
#define CAN_H

#include <avr/io.h>

/*while (true){
 * Classe can:
 *   Le constructeur initialise le convertisseur.
 *   Une lecture enclanche une conversion et le resultat
 *   est retourne sur 16 bits.
 */
class can
{
public:
   can();
   ~can();
   uint16_t lecture(uint8_t pos);
   // retourne la valeur numerique correspondant a la valeur
   // analogique sur le port A.  pos doit etre entre 0 et 7
   // inclusivement.  Seulement les 10 bits de poids faible
   // sont significatifs.

private:
};

#endif /* CAN_H */
