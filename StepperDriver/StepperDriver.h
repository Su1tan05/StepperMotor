#ifndef STEPPER_DRIVER_H
#define STEPPER_DRIVER_H

#include "mbed.h"

/** A class for driving a stepper motor in open loop.
  * A driver must contain an indexer and sequencer.
  * Each generated pulse moves the rotor by one step in a given direction.
  */
class StepperDriver {
    
    public:
    
    /** Constructor receives output pin and direction pin.
      * @param outputPin DigitalOut pin for sending pulses to the driver.
      * @param directionPin DigitalOut pin for setting a direction of rotation.
      */
    StepperDriver(PinName outputPin, PinName directionPin);
    
    /** Sets the motor resolution in steps per revolution (uint32_t) and minimum and maximum 
      * angle in degrees (angles range).
      * @param resolution Resolution of the stepper motor in steps per revolution (uint32_t). 
      * Typical value is 200 steps per revolution, and that value is set by default in this class.
      * @param minDegrees Minimum angle in degrees.
      * @param maxDegrees Maximum angle in degrees.
      */
    void configure(uint32_t resolution, float minDegrees, float maxDegrees);
    
    /** Sets the motor resolution in degrees per step (float) and minimum and maximum 
      * angle in degrees (angles range). 
      * @param resolution Resolution of the stepper motor in degrees per step (float).
      * Typical value is 1.8 degrees per step, and that value is set by default in this class.
      * @param minDegrees Minimum angle in degrees.
      * @param maxDegrees Maximum angle in degrees.
      */
    void configure(float resolution, float minDegrees, float maxDegrees);
    
    /** Sets the position in degrees.
      * @param desiredPosition Desired position in degrees.
      */
    void setPosition(float desiredPosition);
    
    /** Get the current position in degrees.
      * @returns Current position in degrees.
      */
    float getPosition();
    
    /** Set the speed in rpm (revolutions per minute). 
      * @param speedRPM Motor speed in rpm (revolutions per minute).
      */
    void setSpeedRPM(float speedRPM);
    
    /** Set the speed in revolutions per second. 
      * @param speedRPS Motor speed in revolutions per second.
      */
    void setSpeedRPS(float speedRPS);
    
    /** Set the speed in steps per second. 
      * @param speedSPS Motor speed in steps per second.
      */
    void setSpeedSPS(float speedSPS);
    
    /** Get the speed in rpm (revolutions per minute). 
      * @returns Motor speed in rpm (revolutions per minute).
      */
    float getSpeedRPM();
    
    /** Get the speed in revolutions per second. 
      * @returns Motor speed in revolutions per second.
      */
    float getSpeedRPS();
    
    /** Get the speed in steps per second. 
      * @returns Motor speed in steps per second.
      */
    float getSpeedSPS();
    
    /** Set the pulse width in seconds. 
      * @param pulseWidth Pulse width in seconds.
      */
    void setPulseWidth(float pulseWidth);
    
    protected:
    DigitalOut output, direction;
    uint32_t currentPosition, previousPosition, homePosition, minPosition, maxPosition, desiredPosition;
    float degreesPerStep, pulseWidth, speed;
    Ticker ticker;
    Timeout timeout;
    void update();
    void attachTicker();
    void detachTicker();
    void generateImpulse();
    void turnOutputOff();
    bool isTickerAttached;
    void setResolution(uint32_t resolution);
    void setResolution(float resolution);
    void setDegreesRange(float minDegrees, float maxDegrees);
};

#endif