#include "RS232communication.h"

RS232communication::RS232communication()
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void RS232communication::transmitUART(uint8_t data)
{
    do
    {
    } while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = data;
}
unsigned RS232communication::receiveUART()
{
    do
    {
    } while (!(UCSR0A & (1 << RXC0)));

    return UDR0;
}
void RS232communication::transmitMessage(const char *str)
{
    uint8_t i = 0;
    while ((str[i]) != '\0')
    {
        transmitUART(str[i++]);
    }
}
