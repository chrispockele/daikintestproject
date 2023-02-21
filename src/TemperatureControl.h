#ifndef TEMPERATURECONTROL_H
#define TEMPERATURECONTROL_H

#include <exception>


struct TemperatureValueException : public std::exception {
   const char * what () const throw () {
      return "maximum temperature shall be greater than or equal to (minimum temperature + 1)";
   }
};


class TemperatureControl {

    public:
        enum class TemperatureControlState {
            TEMPCTRL_IDLE    ,
            TEMPCTRL_HEATING ,
            TEMPCTRL_COOLING
        };

        TemperatureControl(float minimumTemp, float MaximumTemp);

        void    setMinimumTemperature(float minimumTemp);
        void    setMaximumTemperature(float MaximumTemp);
        float   getMinimumTemperature(void);
        float   getMaximumTemperature(void);

        void    notifyCurrentTemperature(float currentTemp);

        void    outputState();

        TemperatureControlState getCurrentState(void);

    private:
        /* internal representation: int representing units of 0.1 degree Celsius */
        signed int minimumTemp; // in 0.1 degree Celsius
        signed int maximumTemp; // in 0.1 degree Celsius

        TemperatureControlState    currentState;

        void checkTemperatureValuesValid(int pMinTemp, int pMaxTemp); /* parameters in internal representation: int representing units of 0.1 degree Celsius */
};


#endif // TEMPERATURECONTROL_H
