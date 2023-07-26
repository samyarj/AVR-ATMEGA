#include "Sensors.h"

Sensors::Sensors()
{
    activateInMode();
}

uint16_t Sensors::getDistance()
{
    distance = 0;
    //sums the distances of a certain sizeSample
    for (uint8_t i = 0; i < sizeSample_; i++)
    {   
        //reads the signal sent to the analogic-to digital converter and keep the most significative bits
        distance += (can_.lecture(_bit) >> 2);
    }
    //calculates average
    distance /= sizeSample_;
    return distance;
}

bool Sensors::distanceUnder15cm()
{
    return getDistance() > distance15cm_;
}

bool Sensors::distanceUnder30cm()
{
    return getDistance() > distance30cm_;
}

bool Sensors::distanceUnder60cm()
{
    return getDistance() > distance60cm_;
}
