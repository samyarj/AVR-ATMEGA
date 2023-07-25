#include "IOPorts.h"

uint8_t IOPorts::generateMask(uint8_t wantedBit, uint8_t wantedMode)
{
    if (wantedMode == _mode00)
        return (~((1 << wantedBit) | (1 << (wantedBit + 1))));
    else if (wantedMode == _mode01)
        return (1 << wantedBit);
    else if (wantedMode == _mode10)
        return (1 << (wantedBit + 1));
    else
        return ((1 << wantedBit) | (1 << (wantedBit + 1)));
}

void IOPorts::setPort(volatile uint8_t *wantedPort, uint8_t wantedBit, uint8_t wantedMode)
{
    *wantedPort &= generateMask(wantedBit, _mode00);
    if (wantedMode != _mode00)
        *wantedPort |= generateMask(wantedBit, wantedMode);
}

void IOPorts::setIOMode(uint8_t wantedBit, uint8_t wantedMode)
{
    setPort(_ddr, wantedBit, wantedMode);
}

void IOPorts::togglePort(uint8_t wantedBit, uint8_t wantedMode)
{
    setPort(_port, wantedBit, wantedMode);
}