#pragma once

#include <libriccore/riccoresystem.h>

#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include "Sensors/MAX31856.h"

#include "Commands/commands.h"

/* System class: a class which encapsulates all the classes used to describe components on
    the board, creating the board system. Interacting with the board involves interacting
    the system */

class OvenController
{
    public:

        OvenController(MAX31856 &TC, int ssrPin, int updateDelta = 5): _TC(TC), _ssrPin(ssrPin), _updateDelta(updateDelta) {};

        void update(){

            if (millis() - _prevTime > _updateDelta)
            {
                _TC.update();

                if (isnan(_TC.getTemp()))
                {
                }
                else
                {
                    if (_TC.getTemp() < _SetPoint)
                    {
                        digitalWrite(_ssrPin, HIGH);
                    }
                    else
                    {
                        digitalWrite(_ssrPin, LOW);
                    }
                }

                _prevTime = millis();
            }
        };

        void setTemp(float Temp){
            _SetPoint = Temp;
        }

    private:
        MAX31856& _TC;
        int _ssrPin;
        float _SetPoint = 0;
        int _updateDelta = 5;
        long _prevTime = 0;


};