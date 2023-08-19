#ifndef CAN_H
#define CAN_H

#include <avr/io.h>

// A class to control the CAN bus
class can
{
public:
   can();
   ~can();
   uint16_t lecture(uint8_t pos);

private:
};

#endif /* CAN_H */
