// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/sysid/SysIdRoutine.h>

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>

using namespace ctre::phoenix6;

class ArmSubsystem : public frc2::SubsystemBase {
 public: 
 
  ArmSubsystem();

  void ConfigureHardware();
  frc2::CommandPtr SysIdQuasistatic(frc2::sysid::Direction direction);
  frc2::CommandPtr SysIdDynamic(frc2::sysid::Direction direction);

  void TeleopMove(const double omega);
  
  /**
   * Arm command factory method.
   */
  frc2::CommandPtr ArmMethodCommand();

  /**
   * An Arm method querying a boolean state of the subsystem (for Arm, a
   * digital sensor).
   *
   * @return value of some boolean subsystem state, such as a digital sensor.
   */
  bool ArmCondition();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Will be called periodically whenever the CommandScheduler runs during
   * simulation.
   */
  void SimulationPeriodic() override;

  void MoveToSetpoint(units::angle::turn_t setpoint);

 private:
 
 frc2::sysid::SysIdRoutine m_sysIdRoutine;
 
 //CANBus rioBus{"rio"};
 
 hardware::TalonFX  m_armMotor1{26};  
 hardware::TalonFX  m_armMotor2{27};  
 hardware::TalonFX  m_armMotor3{28}; 
 hardware::TalonFX  m_armMotor4{29};

 controls::VelocityVoltage m_velocity = controls::VelocityVoltage{0_tps}.WithSlot(0);

 hardware::CANcoder m_armCANCoder{7};

 controls::MotionMagicVoltage m_request{0_tr};
 
 controls::PositionVoltage m_position = controls::PositionVoltage{0_tr}.WithSlot(0);
 
 // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.


};
