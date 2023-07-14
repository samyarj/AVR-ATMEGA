#ifndef COMMUNICATIONRS232_H
#define COMMUNICATIONRS232_H

#include <avr/io.h>

class communicationRS232
{
public:
    communicationRS232();
    ~communicationRS232();
    void transmettreUART(uint8_t donnee);
    unsigned recevoirUART();
    void transmettreMessage(const char *str);

private:
};
#endif
