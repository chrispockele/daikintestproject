// main.cpp

#include <exception>
#include <iostream>
#include "TemperatureControl.h"

using namespace std;



int main (int argc, char *argv[]) {
    TemperatureControl testObject(17.8, 25.3);

    cout << "Temperature control test program" << endl;
    
    testObject.outputState();
    
    cout << endl << "Setting temperature to 16.0" << endl;
    testObject.notifyCurrentTemperature(16.0);
    testObject.outputState();

    cout << endl << "Setting temperature to 17.0" << endl;
    testObject.notifyCurrentTemperature(17.0);
    testObject.outputState();

    cout << endl << "Setting temperature to 17.7" << endl;
    testObject.notifyCurrentTemperature(17.7);
    testObject.outputState();

    cout << endl << "Setting temperature to 17.8" << endl;
    testObject.notifyCurrentTemperature(17.8);
    testObject.outputState();

    cout << endl << "Setting temperature to 17.9" << endl;
    testObject.notifyCurrentTemperature(17.9);
    testObject.outputState();

    cout << endl << "Setting temperature to 18.7" << endl;
    testObject.notifyCurrentTemperature(18.7);
    testObject.outputState();

    cout << endl << "Setting temperature to 18.8" << endl;
    testObject.notifyCurrentTemperature(18.8);
    testObject.outputState();

    cout << endl << "Setting temperature to 18.9" << endl;
    testObject.notifyCurrentTemperature(18.9);
    testObject.outputState();

    cout << endl << "Setting temperature to 17.8" << endl;
    testObject.notifyCurrentTemperature(17.8);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.0" << endl;
    testObject.notifyCurrentTemperature(25.0);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.1" << endl;
    testObject.notifyCurrentTemperature(25.1);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.2" << endl;
    testObject.notifyCurrentTemperature(25.2);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.3" << endl;
    testObject.notifyCurrentTemperature(25.3);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.4" << endl;
    testObject.notifyCurrentTemperature(25.4);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.5" << endl;
    testObject.notifyCurrentTemperature(25.5);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.4" << endl;
    testObject.notifyCurrentTemperature(25.4);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.3" << endl;
    testObject.notifyCurrentTemperature(25.3);
    testObject.outputState();
    
    cout << endl << "Setting temperature to 25.2" << endl;
    testObject.notifyCurrentTemperature(25.2);
    testObject.outputState();
    
    cout << endl << "Setting temperature to 25.1" << endl;
    testObject.notifyCurrentTemperature(25.1);
    testObject.outputState();

    cout << endl << "Setting temperature to 24.7" << endl;
    testObject.notifyCurrentTemperature(24.7);
    testObject.outputState();

    cout << endl << "Setting temperature to 24.4" << endl;
    testObject.notifyCurrentTemperature(24.4);
    testObject.outputState();

    cout << endl << "Setting temperature to 24.3" << endl;
    testObject.notifyCurrentTemperature(24.3);
    testObject.outputState();

    cout << endl << "Setting temperature to 24.2" << endl;
    testObject.notifyCurrentTemperature(24.2);
    testObject.outputState();

    cout << endl << "Setting temperature to 25.3" << endl;
    testObject.notifyCurrentTemperature(25.3);
    testObject.outputState();

    try {
        cout << endl << "trying to set minimum temperature above maximum" << endl;
        testObject.setMinimumTemperature(33.7); // above the maximum
    } catch(TemperatureValueException& e) {
        cout << "correctly threw exception for invalid values (set minimum above maximum)" << endl;
        cout << "minimum temperature is now " << testObject.getMinimumTemperature() << endl;    // should not have changed
    }
    
    try {
        cout << endl << "trying to set maximum temperature below minimum" << endl;
        testObject.setMaximumTemperature(15.3); // below the minimum
    } catch(TemperatureValueException& e) {
        cout << "correctly threw exception for invalid values (set maximum below minimum)" << endl;
        cout << "maximum temperature is now " << testObject.getMaximumTemperature() << endl;    // should not have changed
    }

    
    try {
        cout << endl << "trying to create a TemperatureControl object with minimum==7 and maximum==-1" << endl;

        TemperatureControl testObject(7, -1);
    } catch(TemperatureValueException& e) {
        cout << "correctly threw exception for invalid values" << endl;
    }
    
    return 0;
}
