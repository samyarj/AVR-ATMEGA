#include "IOPorts.h"

class LED : public IOPorts
{
public:
    LED();
    virtual ~LED();

    void eteindre();
    void allumerRouge();
    void allumerVert();



protected:
    volatile uint8_t *_port = &PORTA;
    volatile uint8_t *_ddr = &DDRA;
    uint8_t _bit = 0;

};
