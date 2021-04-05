#include "mbed.h"
#include "StepperDriver.h"

StepperDriver::StepperDriver(PinName outputPin, PinName directionPin) : output(outputPin), direction(directionPin) {
    currentPosition = previousPosition = desiredPosition = 0;
    configure(1.8f, 0, 360);
    homePosition = (maxPosition - minPosition) / 2;
    setSpeedSPS(250);
    setPulseWidth(100e-6);
}

void StepperDriver::configure(uint32_t resolution, float minDegrees, float maxDegrees) {
    setResolution(resolution);
    setDegreesRange(minDegrees, maxDegrees);
}

void StepperDriver::configure(float resolution, float minDegrees, float maxDegrees) {
    setResolution(resolution);
    setDegreesRange(minDegrees, maxDegrees);
}

void StepperDriver::setPosition(float desiredDegrees) {
    uint32_t position = desiredDegrees / degreesPerStep + 0.5f; // rounding
    if (position >= minPosition && position <= maxPosition) {
        desiredPosition = position;
    }
    if (desiredPosition != currentPosition && !isTickerAttached) {
        attachTicker();
    }
}

float StepperDriver::getPosition() {
    return currentPosition * degreesPerStep;
}

void StepperDriver::update() {
    if (desiredPosition > currentPosition) {
        direction = 1;
        currentPosition++;
        generateImpulse();
    } else if (desiredPosition < currentPosition) {
        direction = 0;
        currentPosition--;
        generateImpulse();
    } else {
        detachTicker();
    }
    previousPosition = currentPosition;
}

void StepperDriver::attachTicker() {
    ticker.attach(this, &StepperDriver::update, 1/speed);
    isTickerAttached = true;
}

void StepperDriver::detachTicker() {
    ticker.detach();
    isTickerAttached = false;
}

void StepperDriver::generateImpulse() {
    output = 1;
    timeout.attach(this, &StepperDriver::turnOutputOff, pulseWidth);
}

void StepperDriver::turnOutputOff() {
    output = 0;
}

void StepperDriver::setResolution(uint32_t resolution) {
    degreesPerStep = 360.0f / resolution;
}

void StepperDriver::setResolution(float resolution) {
    degreesPerStep = resolution;
}

void StepperDriver::setDegreesRange(float minDegrees, float maxDegrees) {
    minPosition = 0;
    maxPosition = minPosition + 1/degreesPerStep * (maxDegrees - minDegrees);
}

void StepperDriver::setSpeedSPS(float speedSPS) {
    speed = speedSPS;
}

void StepperDriver::setSpeedRPS(float speedRPS) {
    speed = speedRPS * 360 / degreesPerStep;
}

void StepperDriver::setSpeedRPM(float speedRPM) {
    speed = speedRPM / 60 * 360 / degreesPerStep;
}

float StepperDriver::getSpeedSPS() {
    return speed;
}

float StepperDriver::getSpeedRPS() {
    return speed * degreesPerStep / 360;
}

float StepperDriver::getSpeedRPM() {
    return speed * degreesPerStep / 360 * 60;
}

void StepperDriver::setPulseWidth(float pulseWidth) {
    if (pulseWidth > 0) {
        this->pulseWidth = pulseWidth;
    }
}