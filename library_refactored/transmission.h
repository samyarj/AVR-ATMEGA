#include <stdio.h>
#include <math.h>
#include <vector>
#include <array>
#include <string.h>

#include <avr/io.h>
#include <util/delay.h>
#include <util/crc16.h>

#include "LEDController.h"
#include "memoire24.h"
#include "RS232communication.h"


// Concrete class for 2D position of objects
class Point
{
public:
    Position(uint32_t x, uint32_t y) : AbsPosition(x, y) {};
};

// Class for serial communication
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
    
    static std::vector<std::array<uint16_t, 2>> createSVGPoints();
    static constexpr std::vector<std::array<uint16_t, 2>> svgpoints = this->createSVGPoints();

    serialCommunication communication;
    Memory24CXXX memory;
    uint8_t poles[32];
    uint8_t nPoles = 0;
    uint16_t area = 0;
    int hullSize = 0;
    void crc32(uint8_t a);
    int orientation(Point point1, Point point2, Point point3);
};
