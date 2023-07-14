#include "communicationRS232.h"
#define F_CPU 8000000
#include <util/delay.h>

communicationRS232::communicationRS232()
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A = 0; // il y aavit pas vrm d info sur la reception ni la transmission

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Du USART vers le PC

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
