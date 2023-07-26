#include "Robot.h"

void initializeAngle(int16_t initAngle)
{
    currentAngle_ = initAngle;
}

void Robot::changeAngle(int16_t rotationAngle) // currentAngle_ must be in between 0 and 360
{
    currentAngle_ += rotationAngle;
    if (currentAngle_ >= 360)
    {
        currentAngle_ -= 360;
    }
    else if (currentAngle_ < 0)
    {
        currentAngle_ += 360;
    }
}

int Robot::getNextTileKey()
{
}