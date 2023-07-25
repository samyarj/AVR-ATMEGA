#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

class IOPorts
{
public:
    IOPorts() = default;
    virtual ~IOPorts() = default;

    virtual uint8_t generateMask(uint8_t wantedBit, uint8_t wantedMode);
    
    virtual void setIOMode(uint8_t wantedBit, uint8_t wantedMode);
    virtual void togglePort(uint8_t wantedBit, uint8_t wantedMode);
    
    void setPort(volatile uint8_t *portVoulu, uint8_t bitVoulu, uint8_t mode); //template method pattern


protected:
    uint8_t _mode00 = 0;
    uint8_t _mode01 = 1;
    uint8_t _mode10 = 2;
    uint8_t _mode11 = 3;

    volatile uint8_t *_port;
    volatile uint8_t *_ddr;
};
