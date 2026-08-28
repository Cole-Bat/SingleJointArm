// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmCommand.h"

ArmCommand::ArmCommand(ArmSubsystem* subsystem)
    : m_arm{subsystem} {
  // Register that this command requires the subsystem.
  AddRequirements(m_arm);
}
