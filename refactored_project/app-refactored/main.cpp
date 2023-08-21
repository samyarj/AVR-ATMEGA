#define F_CPU 8000000UL

#include <stdio.h>
#include "RobotManager.h"
#include "RobotTracker.h"
#include <avr/interrupt.h>

volatile bool wait = true;
volatile bool mode = true;

volatile bool direction = true;
volatile bool up = true;
volatile bool nextPosition = true;

bool detected = true;

volatile Position state;


RobotManage manager;

ISR(INT0_vect)
{
    _delay_ms(30);
    if (controller.interruptButtonIsOn() && wait)
        wait = false;
    else if (controller.interruptButtonIsOn() && direction)
        direction = false;
    else if (controller.interruptButtonIsOn())
        nextPosition = false;
    EIFR |= (1 << INTF0);
}

ISR(PCINT2_vect)
{
    _delay_ms(30);
    {
        for (int i = 0; i < 3; i++)
        {
            controller.startSound(71 + 2 * i);
            _delay_ms(300);
            controller.stopSound();
            _delay_ms(300);
        }
    }

    while (nextPosition && detected)
    {
        for (int i = 0; i < 1000; i++)
        {
            controller.startFlashingLED();
            _delay_us(50);
            controller.stopFLashingLED();
            _delay_us(200);
        }
        controller.turnLEDOff();
        _delay_ms(250);
    }
    controller.turnLEDOff();
}

void positionUp()
{
    controller.turnLEDRed();
    _delay_ms(2000);
    controller.turnLEDOff();
    // Call the method that reinitializes the angle here
}

void positionRight()
{
    controller.turnLEDGreen();
    _delay_ms(2000);
    controller.turnLEDOff();
    // Call the method that reinitializes the angle here
}

void detectionMode()
{
    do
    {
        controller.startFlashingLED();
        _delay_us(30);
        controller.stopFLashingLED();
        _delay_us(150);
    } while (direction);
    if (up)
        positionUp();
    else
        positionRight();
}

void transmitData()
{
    timer1_init();
    SVGTransmission transmission;
    RS232communication communication;

    transmission.readPolePosition();
    transmission.transmitInitialImage(); // rectangle + team name
    transmission.determineNPoles();

    Point polePositionsXY[transmission.getNPoles()];
    transmission.determinePolePoints(polePositionsXY);

    Point hull[transmission.getNPoles()];
    transmission.convexHull(polePositionsXY, hull);

    transmission.calculateArea(hull);

    Point hullSVG[transmission.getHullSize()];
    transmission.determineHullSVG(hullSVG, hull);

    transmission.transmitArea();
    transmission.transmitMiddlePolygon(hullSVG);

    transmission.determinePositionPoints();
    transmission.transmitFinalImage();
    transmission.sendControlSum();

    communication.transmitUART(transmission.getEndTransmission());
    timer1_stop();
}


void transmissionMode()
{
    controller.turnLEDRed();
    _delay_ms(2000);
    transmitData();
}

void choreography()
{
    nextPosition = true;
    movement.resetAngle();
    
    cli();
    Position positionAlgo = choosePosition(movement.getX(), movement.getY());
    algorithm(positionAlgo);

    sei();
    if (detected)
    {
        for (int i = 0; i < 3; i++)
        {
            controller.startSound(71 + 2 * i);
            _delay_ms(300);
            controller.stopSound();
            _delay_ms(300);
        }
    }
}

int main()
{
    controller.initializeInterruptButton();
    controller.initializeWhiteButton();
    while (wait)
        ;
    if (mode)
    {
        detectionMode();
        while (detected)
        {
            choreography();
        }
        // Call the method that writes to memory here
        controller.startSound(45);
        _delay_ms(2000);
        controller.stopSound();

        while (true)
        {
            controller.turnLEDRed();
            _delay_ms(250);
            controller.turnLEDOff();
            _delay_ms(250);
        };
    }
    else
    {
        transmissionMode();
        controller.turnLEDOff();
    }
    while (true)
        ;
    
    return 0;
}
