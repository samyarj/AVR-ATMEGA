#include "communicationRS232.h"
#define F_CPU 8000000
#include <util/delay.h>

communicationRS232::communicationRS232()
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void communicationRS232::transmettreUART(uint8_t donnee)
{
    do
    {
    } while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = donnee;
}
unsigned communicationRS232::recevoirUART(void)
{
    do
    {
    } while (!(UCSR0A & (1 << RXC0)));

    return UDR0;
}
void communicationRS232::transmettreMessage(const char *str)
{
    uint8_t i = 0;
    while ((str[i]) != '\0')
    {
        transmettreUART(str[i++]);
    }
}

communicationRS232::~communicationRS232()
{
}
