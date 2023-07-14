#ifndef DEBUG_H
#define DEBUG_H

#define F_CPU 8000000
#include <avr/io.h>
#include "communicationRS232.h"
#include <string.h>

extern communicationRS232 Uart;
#define DEBUG // à mettre en commentaire ou non au besoin
#ifdef DEBUG

#define DEBUG_PRINT(str) \
                         \
    Uart.transmettreMessage(str);

#else
#define DEBUG_PRINT(str) \
    do                   \
    {                    \
    } while (0) // code mort
#endif

#endif
