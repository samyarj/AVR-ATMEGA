#include "IOPorts.h"

uint8_t IOPorts::generateMask(uint8_t wantedBit, uint8_t wantedMode)
{
    if (wantedMode == _mode00)
        return (~((1 << wantedBit) | (1 << (wantedBit + 1)))); //e.g if wantedBit = 2, return 11110011
    else if (wantedMode == _mode01)
        return (1 << wantedBit); //e.g if wantedBit = 2, return 00000100
    else if (wantedMode == _mode10)
        return (1 << (wantedBit + 1)); //e.g if wantedBit = 2, return 00001000
    else
        return ((1 << wantedBit) | (1 << (wantedBit + 1))); //e.g if wantedBit = 2, return 00001100
}

void IOPorts::setPort(volatile uint8_t *IOObject, uint8_t wantedBit, uint8_t wantedMode)
{
    *IOObject &= generateMask(wantedBit, _mode00); //reset the port or ddr at 00 before making any change
    if (wantedMode != _mode00)
        *IOObject |= generateMask(wantedBit, wantedMode); //set at the wanted mode
}

void IOPorts::setIOMode(uint8_t wantedMode)
{
    setPort(_ddr, _bit, wantedMode); //set the ddr given by subclasses ddr attribute
}

void IOPorts::togglePort(uint8_t wantedMode)
{
    setPort(_port, _bit, wantedMode); //set the port given by subclasses port attribute
}

void IOPorts::activateInMode()
{
    setIOMode(_mode00); //set the port to receive signal. Default mode of a given port.
}

void IOPorts::activateOutMode()
{
    setIOMode(_mode11); //set the port to send signal
}
