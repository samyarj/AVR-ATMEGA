#ifndef CONTROLPORT_H
#define CONTROLPORT_H

class ControlPort
{
public:
    ControlPort();
    ~ControlPort() = default;
    uint8_t genererMask(uint8_t bitVoulu, uint8_t masque);
    void setPort(volatile uint8_t *portVoulu, uint8_t bitVoulu, uint8_t mode);
    void delai(uint32_t delaiVoulu, uint32_t facteur);
    uint32_t facteurMs() { return _MILLISEC; };
    uint32_t facteurS() { return _SEC; };

private:
    uint8_t _mode00 = 0;
    uint8_t _mode01 = 1;
    uint8_t _mode10 = 2;
    uint8_t _mode11 = 3;
    uint32_t _MILLISEC = 1000;
    uint32_t _SEC = 1;
};
#endif