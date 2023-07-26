#include <avr/io.h>
#define F_CPU 8000000

class RS232communication
{
public:
    RS232communication();
    ~RS232communication() = default;
    
    void transmitUART(uint8_t data);
    unsigned receiveUART();
    void transmitMessage(const char *str);

private:
};
