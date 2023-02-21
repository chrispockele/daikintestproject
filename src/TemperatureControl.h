#ifndef TEMPERATURECONTROL_H
#define TEMPERATURECONTROL_H



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

        void setMinimumTemp(float minimumTemp);
        void setMaximumTemp(float MaximumTemp);

        void notifyCurrentTemperature(float currentTemp);

    private:
        signed int minimumTemp; // in 0.1 degree Celsius
        signed int maximumTemp; // in 0.1 degree Celsius

        TemperatureControlState    currentState;

        void outputState(TemperatureControlState s);
};


#endif // TEMPERATURECONTROL_H
