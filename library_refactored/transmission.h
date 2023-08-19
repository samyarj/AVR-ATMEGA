#include <stdio.h>
#include <math.h>

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <util/crc16.h>

#include "LEDController.h"
#include "memoire24.h"
#include "RS232communication.h"

struct Point
{
    int x, y;
};

class SVGTransmission
{
public:
    void readPolePosition();
    void transmitInitialImage();
    void determineNPoles();
    void determinePolePoints(Point *polePositionsXY);
    void convexHull(Point polePositionsXY[], Point *hull);
    void calculateArea(Point hull[]);
    void determineHullSVG(Point *hullSVG, Point *hull);
    void transmitArea();
    void transmitMiddlePolygon(Point *hullSVG);
    void determinePositionPoints();
    void transmitFinalImage();
    void sendControlSum();
    uint8_t getNPoles() { return nPoles; }
    uint16_t getArea() { return area; }
    int getHullSize() { return hullSize; }
    uint8_t getEndTransmission() { return END_TRANSMISSION; }

private:
    uint32_t crc = 0xffffffff;
    uint8_t START_TXT = 0x02;
    uint8_t END_TXT = 0x03;
    uint8_t END_TRANSMISSION = 0x04;
    
    static std::vector<std::array<uint16_t, 2>> createSVGPoints()
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

    static constexpr std::vector<std::array<uint16_t, 2>> svgpoints = createSVGPoints();

    serialCommunication communication;
    Memory24CXXX memory;
    uint8_t poles[32];
    uint8_t nPoles = 0;
    uint16_t area = 0;
    int hullSize = 0;
    void crc32(uint8_t a);
    int orientation(Point point1, Point point2, Point point3);
};
