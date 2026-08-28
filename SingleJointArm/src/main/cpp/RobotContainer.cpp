// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/sysid/SysIdRoutineLog.h>
#include <frc2/command/button/Trigger.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/Command.h>

#include "commands/Autos.h"
#include "commands/ArmCommand.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {

  frc2::RunCommand(
    [this] {
      m_arm.TeleopMove(
        m_driverController.GetRightX());
    }, 
    {&m_arm});

  
    // Configure your trigger bindings here

  // // Schedule `ArmCommand` when `ArmCondition` changes to `true`
  // frc2::Trigger([this] {
  //   return m_arm.ArmCondition();
  // }).OnTrue(ArmCommand(&m_arm).ToPtr());

  // Schedule `ArmMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  (m_driverController.Y() && m_driverController.LeftBumper()).WhileTrue(m_arm.SysIdQuasistatic(frc2::sysid::Direction::kForward));
  (m_driverController.B() && m_driverController.LeftBumper()).WhileTrue(m_arm.SysIdQuasistatic(frc2::sysid::Direction::kReverse));
  (m_driverController.A() && m_driverController.LeftBumper()).WhileTrue(m_arm.SysIdDynamic(frc2::sysid::Direction::kForward));
  (m_driverController.X() && m_driverController.LeftBumper()).WhileTrue(m_arm.SysIdDynamic(frc2::sysid::Direction::kReverse));


  // should move the setpoint to a constant value in the constants folder
  (m_driverController.A() && m_driverController.RightBumper()).OnTrue(
    m_arm.RunOnce([this] () {m_arm.MoveToSetpoint();})
  );
  // create bindings for a couple of setpoints
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An Arm command will be run in autonomous
  return autos::ArmAuto(&m_arm);
}
