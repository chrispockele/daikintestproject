
#include <exception>
#include <iostream>

#include "gtest/gtest.h"

#include "TemperatureControl.h"


class TemperatureControlTest : public ::testing::Test {
    protected:
        void SetUp() override {
            tempCtrlUnderTest = new TemperatureControl(17.8, 25.3);
        }

        void TearDown() override {
            delete tempCtrlUnderTest;
        }

        //TemperatureControl tempCtrlUnderTest(17.8, 25.3);
        TemperatureControl* tempCtrlUnderTest;
};



TEST_F(TemperatureControlTest, IsIdleInitially) {
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "Controller did not start out IDLE";
}


TEST_F(TemperatureControlTest, startStopHeatingWorks) {
    tempCtrlUnderTest->notifyCurrentTemperature(20.0);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";
    
    tempCtrlUnderTest->notifyCurrentTemperature(17.8);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";

    // temperature drops below minimum: should start heating
    tempCtrlUnderTest->notifyCurrentTemperature(17.7);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state should switch to HEATING";

    tempCtrlUnderTest->notifyCurrentTemperature(16.0);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected HEATING";

    tempCtrlUnderTest->notifyCurrentTemperature(17.0);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected HEATING";

    tempCtrlUnderTest->notifyCurrentTemperature(17.7);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected HEATING";

    // should stop heating when temperature reaches minimum + 1
    tempCtrlUnderTest->notifyCurrentTemperature(17.8);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected HEATING";

    tempCtrlUnderTest->notifyCurrentTemperature(17.9);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected HEATING";

    tempCtrlUnderTest->notifyCurrentTemperature(18.7);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected HEATING";

    tempCtrlUnderTest->notifyCurrentTemperature(18.8);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state should switch to IDLE";

    tempCtrlUnderTest->notifyCurrentTemperature(18.9);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";

    tempCtrlUnderTest->notifyCurrentTemperature(17.8);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";
}

TEST_F(TemperatureControlTest, startStopCoolingWorks) {
    tempCtrlUnderTest->notifyCurrentTemperature(25.0);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";

    tempCtrlUnderTest->notifyCurrentTemperature(25.1);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";

    tempCtrlUnderTest->notifyCurrentTemperature(25.2);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";

    tempCtrlUnderTest->notifyCurrentTemperature(25.3);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";

    // start heating when temperature exceeds maximum
    tempCtrlUnderTest->notifyCurrentTemperature(25.4);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state should switch to COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(25.5);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(25.4);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    // stop cooling when temperature drops to maximum - 1 or below
    tempCtrlUnderTest->notifyCurrentTemperature(25.3);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(25.2);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(25.1);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(24.7);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(24.4);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(24.3);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state should switch to IDLE";
    
    tempCtrlUnderTest->notifyCurrentTemperature(24.2);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";
    
    tempCtrlUnderTest->notifyCurrentTemperature(25.3);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";
}


TEST_F(TemperatureControlTest, setTemperatureLimitsWorks) {
    // first, test edge case of only 1 degree difference
    tempCtrlUnderTest->setMinimumTemperature(19.0);
    tempCtrlUnderTest->setMaximumTemperature(20.0);
    
    tempCtrlUnderTest->notifyCurrentTemperature(18.9);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected IDLE";
   
    tempCtrlUnderTest->notifyCurrentTemperature(19.5);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected HEATING";

    tempCtrlUnderTest->notifyCurrentTemperature(19.9);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_HEATING) << "state is not the expected HEATING";
    
    tempCtrlUnderTest->notifyCurrentTemperature(20.0);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";

    tempCtrlUnderTest->notifyCurrentTemperature(20.1);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(19.5);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(19.1);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_COOLING) << "state is not the expected COOLING";

    tempCtrlUnderTest->notifyCurrentTemperature(19.0);
    EXPECT_EQ(tempCtrlUnderTest->getCurrentState(), TemperatureControl::TemperatureControlState::TEMPCTRL_IDLE) << "state is not the expected IDLE";

    EXPECT_THROW( tempCtrlUnderTest->setMinimumTemperature(30), TemperatureValueException ) << "Setting minimum temperature above maximum should throw an exception of type TemperatureValueException";
    EXPECT_FLOAT_EQ(tempCtrlUnderTest->getMinimumTemperature(), 19.0)  << "Minimum temperature should not have changed!";

    EXPECT_THROW( tempCtrlUnderTest->setMaximumTemperature(10), TemperatureValueException ) << "Setting maximum temperature below minimum should throw an exception of type TemperatureValueException";
    EXPECT_FLOAT_EQ(tempCtrlUnderTest->getMaximumTemperature(), 20.0)  << "Maximum temperature should not have changed!";

    EXPECT_THROW( new TemperatureControl(25.8, 10.3), TemperatureValueException ) << "Creating a TemperatureControl object with maximum temperature below minimum should throw an exception of type TemperatureValueException";
}


