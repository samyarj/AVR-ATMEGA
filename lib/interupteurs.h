#ifndef INTERUPT_H
#define INTERUPT_H
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "controlPort.h"

class Interupt : public ControlPort
{
public:
  Interupt()
  {
    setPort(_DDR_INTERRUPTEUR, _BIT_INTERRUPTEUR, _MODE_ENTREE);
  };
  ~Interupt() = default;

  bool verifierPIN();
  void filtreAntiRebondScrutation(bool appuyer);
  void initialisationInterrupt();
  bool appuyer() { return _appuyer; };
  bool relacher() { return _relacher; };

protected:
  uint8_t _MODE_ENTREE = 0;
  const uint8_t _BIT1_ALLUMER = 1;
  const uint8_t _DELAI_ANTIREBOND = 10;
  const bool _appuyer = true;
  const bool _relacher = false;

private:
  volatile uint8_t *_DDR_INTERRUPTEUR = &DDRD;
  volatile uint8_t *_PIN_INTERRUPTEUR = &PIND;
  uint8_t _BIT_INTERRUPTEUR = 2;
};

class BoutonBlanc : public Interupt
{
  volatile uint8_t *_DDR_INTERRUPTEUR = &DDRC;
  volatile uint8_t *_PIN_INTERRUPTEUR = &PINC;
  uint8_t _BIT_INTERRUPTEUR = 0;
  
  public:
    bool verifierPIN();
    void filtreAntiRebondScrutation(bool appuyer);
    void initialisationInterrupt();
    void desinitialisationInterrupt();
};
#endif
