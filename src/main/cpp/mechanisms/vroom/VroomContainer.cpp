
//====================================================================================================================================================
// Copyright 2026 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#include "mechanisms/vroom/VroomContainer.h"

// FRC Includes
#include "wpi/commands2/button/RobotModeTriggers.hpp"
#include "wpi/commands2/button/Trigger.hpp"

// Team 302 Includes
#include "mechanisms/MechanismTypes.h"
#include "mechanisms/configs/MechanismConfig.h"
#include "mechanisms/configs/MechanismConfigMgr.h"
#include "mechanisms/vroom/Vroom.h"
#include "teleopcontrol/TeleopControl.h"
#include "teleopcontrol/TeleopControlFunctions.h"
#include "utils/logging/debug/Logger.h"

VroomContainer *VroomContainer::m_instance = nullptr;
VroomContainer *VroomContainer::GetInstance()
{
    if (VroomContainer::m_instance == nullptr)
    {
        VroomContainer::m_instance = new VroomContainer();
    }
    return VroomContainer::m_instance;
}

VroomContainer::VroomContainer()
{
}

void VroomContainer::ConfigureBindings()
{
    auto config = MechanismConfigMgr::GetInstance()->GetCurrentConfig();
    if (config == nullptr)
    {
        return;
    }

    auto mech = config->GetMechanism(MechanismTypes::MECHANISM_TYPE::VROOM);
    m_vroom = (mech != nullptr) ? dynamic_cast<Vroom *>(mech) : nullptr;
    if (m_vroom == nullptr)
    {
        // Vroom not present on this robot (commented out in the per-robot config) - nothing to bind.
        return;
    }

    auto controller = TeleopControl::GetInstance();
    if (controller == nullptr)
    {
        return;
    }
    auto considerGamePadTransitions = wpi::cmd::RobotModeTriggers::Teleop();

    //==============================================================================================
    // Binding table.
    //
    // One line per command. The transition logic for each command lives in its matching
    // Get<Command>Trigger() method further down, so this table stays a flat, readable list and the
    // per-command conditions can be regenerated/edited in isolation. Each command picks the binding
    // flavor that fits it:
    //
    //   .WhileTrue(cmd) - "held" command: scheduled on the condition's false->true edge, CANCELLED on
    //                     its true->false edge. Falls back to the default command the moment the
    //                     condition stops being true.
    //   .OnTrue(cmd)    - "self-governing" command: scheduled on the false->true edge, then left alone.
    //                     Runs until its OWN IsFinished() returns true (or another command interrupts by
    //                     requiring the subsystem).
    //
    // The resting state is bound as the subsystem's DEFAULT command - it runs whenever no other command
    // requires the subsystem.
    //==============================================================================================

    // Default Command
    m_vroom->SetDefaultCommand(m_vroom->GetOffCommand());

    GetIntakeTrigger().WhileTrue(m_vroom->GetIntakeCommand());
    GetExpelTrigger().WhileTrue(m_vroom->GetExpelCommand());
    GetSpinUpLongTrigger().WhileTrue(m_vroom->GetSpinUpLongCommand().AndThen(m_vroom->GetLongShotCommand()));

    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, std::string("VroomContainer"), std::string("Configured"), std::string("Vroom"));
}

//==================================================================================================
// Per-command transition triggers
//==================================================================================================
wpi::cmd::Trigger VroomContainer::GetOffTrigger()
{
    // Create trigger for  Off Command
    /*
    Exmample:
    Mech *mech = m_mech;
    return wpi::cmd::Trigger([mech]()
                             { return mech->Method; });
    or
    return wpi::cmd::RobotModeTriggers::Teleop() && TeleopControl::GetInstance()->GetCommandTrigger(TeleopControlFunctions::Function);
    */

    return wpi::cmd::Trigger([]()
                             { return false; });
}
wpi::cmd::Trigger VroomContainer::GetIntakeTrigger()
{
    // Create trigger for  Intake Command
    /*
    Exmample:
    Mech *mech = m_mech;
    return wpi::cmd::Trigger([mech]()
                             { return mech->Method; });
    or
    return wpi::cmd::RobotModeTriggers::Teleop() && TeleopControl::GetInstance()->GetCommandTrigger(TeleopControlFunctions::Function);
    */

    return wpi::cmd::RobotModeTriggers::Teleop() && TeleopControl::GetInstance()->GetCommandTrigger(TeleopControlFunctions::INTAKE);
}
wpi::cmd::Trigger VroomContainer::GetExpelTrigger()
{
    // Create trigger for  Expel Command
    /*
    Exmample:
    Mech *mech = m_mech;
    return wpi::cmd::Trigger([mech]()
                             { return mech->Method; });
    or
    return wpi::cmd::RobotModeTriggers::Teleop() && TeleopControl::GetInstance()->GetCommandTrigger(TeleopControlFunctions::Function);
    */

    return wpi::cmd::Trigger([]()
                             { return false; });
}
wpi::cmd::Trigger VroomContainer::GetSpinUpShortTrigger()
{
    // Create trigger for  SpinUpShort Command
    /*
    Exmample:
    Mech *mech = m_mech;
    return wpi::cmd::Trigger([mech]()
                             { return mech->Method; });
    or
    return wpi::cmd::RobotModeTriggers::Teleop() && TeleopControl::GetInstance()->GetCommandTrigger(TeleopControlFunctions::Function);
    */

    return wpi::cmd::RobotModeTriggers::Teleop() && TeleopControl::GetInstance()->GetCommandTrigger(TeleopControlFunctions::SHORT_LAUNCH);
}
wpi::cmd::Trigger VroomContainer::GetShortShotTrigger()
{
    // Create trigger for  ShortShot Command
    /*
    Exmample:
    Mech *mech = m_mech;
    return wpi::cmd::Trigger([mech]()
                             { return mech->Method; });
    or
    return wpi::cmd::RobotModeTriggers::Teleop() && TeleopControl::GetInstance()->GetCommandTrigger(TeleopControlFunctions::Function);
    */
    return wpi::cmd::Trigger([]()
                             { return false; });
}
wpi::cmd::Trigger VroomContainer::GetSpinUpLongTrigger()
{
    // Create trigger for  SpinUpLong Command
    /*
    Exmample:
    Mech *mech = m_mech;
    return wpi::cmd::Trigger([mech]()
                             { return mech->Method; });
    or
    */
    return wpi::cmd::RobotModeTriggers::Teleop() && TeleopControl::GetInstance()->GetCommandTrigger(TeleopControlFunctions::LONG_LAUNCH);
}
wpi::cmd::Trigger VroomContainer::GetLongShotTrigger()
{
    // Create trigger for  LongShot Command
    /*
    Exmample:
    Mech *mech = m_mech;
    return wpi::cmd::Trigger([mech]()
                             { return mech->Method; });
    or
     */
    return wpi::cmd::Trigger([]()
                             { return false; });
}
