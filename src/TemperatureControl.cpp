#include "TemperatureControl.h"

#include <cmath>
#include <exception>
#include <iostream>

   
#define CAST_FLOAT_TEMPERATURE_TO_INT_REPRESENTATION(pFloatTemp)  ( static_cast<int>(round((pFloatTemp) * 10)) )       /* internal representation: int representing units of 0.1 degree Celsius */
#define CAST_INT_REPRESENTATION_TO_FLOAT_TEMPERATURE(pInt10Temp)  ( static_cast<float>( (pInt10Temp) ) / 10 )
        
        
TemperatureControl::TemperatureControl(float pMinTemp, float pMaxTemp) : 
        minimumTemp(170),
        maximumTemp(250),
        currentState(TemperatureControlState::TEMPCTRL_IDLE)             
{
    //this->currentState = TemperatureControlState::TEMPCTRL_IDLE;
    int minTemp;
    int maxTemp;

    minTemp = CAST_FLOAT_TEMPERATURE_TO_INT_REPRESENTATION(pMinTemp);
    maxTemp = CAST_FLOAT_TEMPERATURE_TO_INT_REPRESENTATION(pMaxTemp);
    checkTemperatureValuesValid(minTemp, maxTemp);

    this->minimumTemp = minTemp;
    this->maximumTemp = maxTemp;

    // start by idling as long as no temperature is specified
    notifyCurrentTemperature( (pMinTemp + pMaxTemp) / 2 );
}

void TemperatureControl::setMinimumTemperature(float pMinTemp) {
    int minTemp;

    minTemp = CAST_FLOAT_TEMPERATURE_TO_INT_REPRESENTATION(pMinTemp);
    checkTemperatureValuesValid(minTemp, this->maximumTemp);

    this->minimumTemp = minTemp;
}

void TemperatureControl::setMaximumTemperature(float pMaxTemp) {
    int maxTemp;

    maxTemp = CAST_FLOAT_TEMPERATURE_TO_INT_REPRESENTATION(pMaxTemp);
    checkTemperatureValuesValid(this->minimumTemp, maxTemp);

    this->maximumTemp = maxTemp;
}


float TemperatureControl::getMinimumTemperature(void) {
    return CAST_INT_REPRESENTATION_TO_FLOAT_TEMPERATURE(this->minimumTemp);
}

float TemperatureControl::getMaximumTemperature(void) {
    return CAST_INT_REPRESENTATION_TO_FLOAT_TEMPERATURE(this->maximumTemp);
}


void TemperatureControl::notifyCurrentTemperature(float pCurrentTemp) {
    TemperatureControlState newState;;
    int                     currentTemp10;  // current temperature in units of 0.1 degrees Celsius
    
    newState      = currentState;
    currentTemp10 = CAST_FLOAT_TEMPERATURE_TO_INT_REPRESENTATION(pCurrentTemp);
    
    if(TemperatureControlState::TEMPCTRL_HEATING == currentState) {
        if(currentTemp10 >= (this->minimumTemp + 10)) {
            // temperature reached "minimum + 1" deg C, stop heating
            newState = TemperatureControlState::TEMPCTRL_IDLE;
        }
    }

    if(TemperatureControlState::TEMPCTRL_COOLING == currentState) {
        if(currentTemp10 <= (this->maximumTemp - 10)) {
            // temperature reached "maximum - 1" deg C, stop cooling
            newState = TemperatureControlState::TEMPCTRL_IDLE;
        }
    }
    
    if(currentTemp10 < this->minimumTemp) {
        newState = TemperatureControlState::TEMPCTRL_HEATING;
    }

    if(currentTemp10 > this->maximumTemp) {
        newState = TemperatureControlState::TEMPCTRL_COOLING;
    }

    if(newState != this->currentState) {
        this->currentState = newState;
        // startHeating() , cooling, idling ...
        
        if(TemperatureControlState::TEMPCTRL_HEATING == newState) {
            // In a real system: call an interface to command the hardware to start heating
            std::cout << " * TemperatureControl: Start heating..." << std::endl;
        }

        if(TemperatureControlState::TEMPCTRL_COOLING == newState) {
            // In a real system: call an interface to command the hardware to start cooling
            std::cout << " * TemperatureControl: Start cooling..." << std::endl;
        }

        if(TemperatureControlState::TEMPCTRL_IDLE == newState) {
            // In a real system: call an interface to command the hardware to stop heating or cooling
            std::cout << " * TemperatureControl: Stop heating / cooling..." << std::endl;
        }
        outputState();
    }
}

        
void TemperatureControl::outputState() {
        std::cout << " * TemperatureControl: state: ";
        switch(this->currentState) {
            case TemperatureControlState::TEMPCTRL_IDLE:
                std::cout << "IDLE";
                break;
            case TemperatureControlState::TEMPCTRL_HEATING:
                std::cout << "HEATING";
                break;
            case TemperatureControlState::TEMPCTRL_COOLING:
                std::cout << "COOLING";
                break;
        }
        std::cout << std::endl;
}


void TemperatureControl::checkTemperatureValuesValid(int pMinTemp, int pMaxTemp) {
    /* check derived requirement Z: maximum temperature shall be equal to or greater than "minimum temperature + 1". */
    if( !( pMaxTemp >= (pMinTemp + 10) ) ) {
        throw TemperatureValueException();
    }
}


TemperatureControl::TemperatureControlState TemperatureControl::getCurrentState(void) {
    return this->currentState;
}

