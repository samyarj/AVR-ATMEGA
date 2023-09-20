#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "controlPort.h"

ControlPort::ControlPort()
{
}
uint8_t ControlPort::genererMask(uint8_t bitVoulu, uint8_t masque)
{
  if (masque == _mode00)
    return (~((1 << bitVoulu) | (1 << (bitVoulu + 1))));
  else if (masque == _mode01)
    return (1 << bitVoulu);
  else if (masque == _mode10)
    return (1 << (bitVoulu + 1));
  else
    return ((1 << bitVoulu) | (1 << (bitVoulu + 1)));
}

void ControlPort::setPort(volatile uint8_t *portVoulu, uint8_t bitVoulu, uint8_t mode)
{
  *portVoulu &= genererMask(bitVoulu, _mode00);
  if (mode != _mode00)
    *portVoulu |= genererMask(bitVoulu, mode);
}

void ControlPort::delai(uint32_t delaiVoulu, uint32_t facteur)
{
  if (facteur == _SEC)
  {
    for (uint32_t i = 0; i < delaiVoulu; i++)
      delai(_MILLISEC, _MILLISEC);
  }
  else if (facteur == _MILLISEC)
  {
    for (uint32_t j = 0; j < delaiVoulu; j++)
      _delay_ms(1);
  }
}