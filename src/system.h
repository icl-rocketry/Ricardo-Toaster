#pragma once

#include <libriccore/riccoresystem.h>

#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include "Sensors/MAX31856.h"

#include "Commands/commands.h"
#include "OvenController.h"

/* System class: a class which encapsulates all the classes used to describe components on
    the board, creating the board system. Interacting with the board involves interacting
    the system */

class System : public RicCoreSystem<System,SYSTEM_FLAG,Commands::ID>
{
    public:

        System();
        
        void systemSetup();

        void systemUpdate();
        //2 seperate SPI lines:
        SPIClass SDSPI; //SPI for the SD card
        SPIClass SNSRSPI; //SPI for the sensors
        //4 thermocouples:
        MAX31856 TC0;
        MAX31856 TC1;
        MAX31856 TC2;
        MAX31856 TC3;

        OvenController ReflowOven;


    // private:


};