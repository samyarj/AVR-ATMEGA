#include "transmission.h"

static std::vector<std::array<uint16_t, 2>> SVGTransmission::createSVGPoints()
{
    std::vector<std::array<uint16_t, 2>> svgpoints;
    for (uint16_t x = 188; x <= 958; x += 110)
    {
        for (uint16_t y = 450; y >= 120; y -= 110)
        {
            svgpoints.push_back({x, y});
        }
    }
    return svgpoints;
}

void SVGTransmission::crc32(uint8_t a)
{
    uint8_t i;
    crc ^= a;
    for (i = 0; i < 8; ++i)
    {
        if (crc & 1)
            crc = (crc >> 1) ^ 0xEDB88320;
        else
            crc = (crc >> 1);
    }
}

int SVGTransmission::orientation(Point point1, Point point2, Point point3)
{
    int val = (point2.y - point1.y) * (point3.x - point2.x) -
              (point2.x - point1.x) * (point3.y - point2.y);
    if (val == 0)
        return 0; // The points are colinear
    else if (val > 0)
        return 1; // Clockwise direction
    else
        return 2; // Counter-clockwise direction
}

void SVGTransmission::readPolePosition()
{
    for (int i = 0; i < 32; i++)
    {
        memory.read(i, &poles[i]);
        _delay_ms(5);
    }
}

void SVGTransmission::transmitInitialImage()
{
    char svgInitial[] = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%\" height=\"100%\" viewBox=\"0 0 1152 576\">"
                        "<rect x=\"96\" y=\"48\" width=\"960\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/> <text x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\"> Section 03 -- Team 6163 -- Pac Bot </text>";
    uint16_t nCharactersInitialImage = strlen(svgInitial);
    communication.transmitUART(START_TXT);
    for (uint16_t i = 0; i < nCharactersInitialImage; i++)
    {
        communication.transmitUART(svgInitial[i]);
        crc32(svgInitial[i]);
    }
}

void SVGTransmission::determineNPoles()
{
    for (int i = 0; i < 32; i++)
    {
        if (poles[i] == 1)
        {
            nPoles++;
        }
    }
}

void SVGTransmission::determinePolePoints(Point *polePositionsXY)
{
    int counter = 0;
    for (int i = 0; i < 32; i++)
    {
        if (poles[i] == 1)
        {
            polePositionsXY[counter].x = i / 4;
            polePositionsXY[counter].y = i - 4 * polePositionsXY[counter].x;
            counter++;
        }
    }
}

void SVGTransmission::convexHull(Point polePositionsXY[], Point *hull)
{
    // Base case: if there are fewer than 3 points, then all points are on the convex hull
    if (nPoles < 3)
    {
        for (int i = 0; i < nPoles; i++)
        {
            hull[i] = polePositionsXY[i];
        }
        hullSize = nPoles;
    }
    else
    {
        // Find the leftmost point
        int leftmostPoint = 0;
        for (int i = 1; i < nPoles; i++)
        {
            if (polePositionsXY[i].x < polePositionsXY[leftmostPoint].x)
            {
                leftmostPoint = i;
            }
        }

        int currentPoint = leftmostPoint; // Current point on the convex hull
        int nextPoint;  // Next point on the convex hull

        do
        {
            // Add the current point to the convex hull
            hull[hullSize] = polePositionsXY[currentPoint];
            hullSize++;
            // Find the next point on the convex hull
            nextPoint = (currentPoint + 1) % nPoles;
            for (int i = 0; i < nPoles; i++)
            {
                // If point i is more to the left than the current point with respect to the current point and the next point
                if (orientation(polePositionsXY[currentPoint], polePositionsXY[i], polePositionsXY[nextPoint]) == 2)
                {
                    nextPoint = i;
                }
            }
            currentPoint = nextPoint;  // Update the current point for the next iteration
        } while (currentPoint != leftmostPoint); // Stop when we return to the starting point
    }
}

void SVGTransmission::calculateArea(Point hull[])
{
    for (int i = 0; i < hullSize; i++)
    {
        area += (((hull[i].x) * (hull[(i + 1) % hullSize].y)) - ((hull[(i + 1) % hullSize].x) * hull[i].y));
    }
    area *= 121; // 11 squared
    area /= 2;
    if (area < 0)
        area *= -1;
}

void SVGTransmission::determineHullSVG(Point *hullSVG, Point *hull)
{
    for (int i = 0; i < hullSize; i++)
    {
        hullSVG[i].x = svgpoints[4 * hull[i].x + hull[i].y][0];
        hullSVG[i].y = svgpoints[4 * hull[i].x + hull[i].y][1];
    }
}

void SVGTransmission::transmitArea()
{
    uint16_t nCharactersArea;
    char areaPolygon[100];
    nCharactersArea = sprintf(areaPolygon, "<text x=\"96\" y=\"553\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">AREA: %d square inches</text>", area);
    for (uint16_t i = 0; i < nCharactersArea; i++)
    {
        communication.transmitUART(areaPolygon[i]);
        crc32(areaPolygon[i]);
    }
}

void SVGTransmission::transmitMiddlePolygon(Point *hullSVG)
{
    char middlePolygon[100];
    middlePolygon[0] = '\0';

    for (uint8_t i = 0; i < hullSize; i++)
    {
        char string[20];
        sprintf(string, "%d,%d ", hullSVG[i].x, hullSVG[i].y);
        strcat(middlePolygon, string);
    }

    char areaPolygon[200];
    sprintf(areaPolygon, "<polygon points=\"%s\" width=\"770\" height=\"10\" stroke=\"black\" stroke-width=\"2\" fill=\"green\" />", middlePolygon);

    communication.transmitMessage(areaPolygon);
    uint16_t nCharacters = strlen(areaPolygon);
    for (uint16_t i = 0; i < nCharacters; i++)
    {
        crc32(areaPolygon[i]);
    }
}

void SVGTransmission::determinePositionPoints()
{
    for (uint8_t i = 0; i < 32; i++)
    {
        uint8_t nCharacters;
        char buffer[100];
        if ((i == 0) && (poles[i] == 0))
        {
            nCharacters = sprintf(buffer,
                                  "<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" stroke=\"red\" stroke-width=\"1\" fill=\"red\"/>",
                                  svgpoints[i][0], svgpoints[i][1]);
        }
        else if ((poles[i] == 1))
        {
            nCharacters = sprintf(buffer, "<circle cx=\"%d\" cy=\"%d\" r=\"10\" stroke=\"black\" stroke-width=\"1\" fill=\"grey\" />",
                                  svgpoints[i][0], svgpoints[i][1]);
        }
        else
        {
            nCharacters = sprintf(buffer, "<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>",
                                  svgpoints[i][0], svgpoints[i][1]);
        }
        for (uint16_t i = 0; i < nCharacters; i++)
        {
            communication.transmitUART(buffer[i]);
            crc32(buffer[i]);
        }
    }
}

void SVGTransmission::transmitFinalImage()
{
    char svgEnd[] = "</svg>";
    uint8_t nCharactersSvgEnd = strlen(svgEnd);
    for (uint8_t i = 0; i < nCharactersSvgEnd; i++)
    {
        communication.transmitUART(svgEnd[i]);
        crc32(svgEnd[i]);
    }
    communication.transmitUART(END_TXT);
}

void SVGTransmission::sendControlSum()
{
    char buffer[9];
    crc = ~crc;
    uint16_t msbCrc = crc >> 16;
    uint16_t lsbCrc = crc;
    uint8_t nCharacters = sprintf(buffer, "%x%x", msbCrc, lsbCrc);
    for (uint8_t i = 0; i < nCharacters; i++)
    {
        communication.transmitUART(buffer[i]);
    }
}
