#pragma once

#include <stdint.h>
#include <unordered_map>
#include <functional>
#include <initializer_list>

#include <libriccore/commands/commandhandler.h>
#include <librnp/rnp_packet.h>

#include "Config/forward_decl.h"
#include "Commands/commands.h"


namespace Commands
{
    enum class ID : uint8_t
    {
        NoCommand = 0,
        Telemcommand = 8,
        setTempCommand = 69,
        Free_Ram = 250
    };

    inline std::initializer_list<ID> defaultEnabledCommands = {ID::Free_Ram,ID::Telemcommand};

    inline std::unordered_map<ID, std::function<void(ForwardDecl_SystemClass &, const RnpPacketSerialized &)>> command_map{
        {ID::Free_Ram, FreeRamCommand},{ID::Telemcommand, TelemetryCommand},{ID::setTempCommand, setTempCommand}};



};