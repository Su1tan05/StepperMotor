#include "mbed.h"
#include "StepperDriver.h"

StepperDriver Motor1(D6,D7);

int main()
{
    Motor1.setSpeedRPM(100);
    while (true) {
        Motor1.setPosition(360);
        wait(1);
        Motor1.setPosition(180);
        wait(1);
        Motor1.setPosition(0);
        wait(1);
    }
}

