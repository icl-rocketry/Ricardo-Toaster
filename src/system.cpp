#include "system.h"

#include <memory>

#include <libriccore/riccoresystem.h>

#include <HardwareSerial.h>

#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include "Config/general_config.h"

#include "Commands/commands.h"

#include "States/idle.h"

#ifdef CONFIG_IDF_TARGET_ESP32S3
static constexpr int VSPI_BUS_NUM = 0;
static constexpr int HSPI_BUS_NUM = 1;
#else
static constexpr int VSPI_BUS_NUM = VSPI;
static constexpr int HSPI_BUS_NUM = HSPI;
#endif

System::System():
RicCoreSystem(Commands::command_map,Commands::defaultEnabledCommands,Serial),
SDSPI(VSPI_BUS_NUM),
SNSRSPI(HSPI_BUS_NUM),
TC0(SNSRSPI, PinMap::TC0_Cs),
TC1(SNSRSPI, PinMap::TC1_Cs),
TC2(SNSRSPI, PinMap::TC2_Cs),
TC3(SNSRSPI, PinMap::TC3_Cs),
ReflowOven(TC0, PinMap::ssrPin)
{};


void System::systemSetup(){
    
    Serial.setRxBufferSize(GeneralConfig::SerialRxSize);
    Serial.begin(GeneralConfig::SerialBaud);
   
    //intialize rnp message logger
    loggerhandler.retrieve_logger<RicCoreLoggingConfig::LOGGERS::SYS>().initialize(networkmanager);

    //initialize statemachine with idle state
    statemachine.initalize(std::make_unique<Idle>(systemstatus,commandhandler));
    //any other setup goes here

    networkmanager.setNodeType(NODETYPE::HUB);
    networkmanager.setNoRouteAction(NOROUTE_ACTION::BROADCAST,{1});

    SNSRSPI.begin(PinMap::SNSR_SCLK,PinMap::SNSR_MISO,PinMap::SNSR_MOSI);
    SNSRSPI.setFrequency(5000000);
    SNSRSPI.setBitOrder(MSBFIRST);
    SNSRSPI.setDataMode(SPI_MODE1);
    SNSRSPI.setClockDivider(SPI_CLOCK_DIV16);
    
    pinMode(PinMap::TC0_Cs, OUTPUT);
    pinMode(PinMap::TC1_Cs, OUTPUT);
    pinMode(PinMap::TC2_Cs, OUTPUT);
    pinMode(PinMap::TC3_Cs, OUTPUT);

    digitalWrite(PinMap::TC0_Cs, HIGH);
    digitalWrite(PinMap::TC1_Cs, HIGH);
    digitalWrite(PinMap::TC2_Cs, HIGH);
    digitalWrite(PinMap::TC3_Cs, HIGH);

    //Thermocouples:
    TC0.setup();
    TC1.setup();
    TC2.setup();
    TC3.setup();

   


};

void System::systemUpdate(){

    ReflowOven.update();
    
};