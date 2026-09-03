// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ArmSubsystem.h"

#include <frc2/command/sysid/SysIdRoutine.h>

#include <ctre/phoenix6/configs/Configuration.hpp>
#include <ctre/phoenix6/TalonFX.hpp>

#include <Constants.h>

using namespace ctre::phoenix6;

ArmSubsystem::ArmSubsystem()
  : m_sysIdRoutine{
      frc2::sysid::Config{1_V / 1_s, 4_V, 10_s, nullptr},
      frc2::sysid::Mechanism{
        [this] (units::volt_t voltage) {
        m_armMotor1.SetVoltage(voltage);
        },
        [this] (frc::sysid::SysIdRoutineLog* log) {
        log->Motor("Arm Motor")
          .voltage(m_armMotor1.GetMotorVoltage().GetValue())
          .position(units::angle::turn_t(m_armCANCoder.GetPosition().GetValue()))
          .velocity(units::angular_velocity::turns_per_second_t(m_armCANCoder.GetVelocity().GetValue()));
        },
        this
      }
  }

{
  ConfigureHardware();
}

frc2::CommandPtr ArmSubsystem::SysIdQuasistatic(frc2::sysid::Direction direction){
    return ArmSubsystem::m_sysIdRoutine.Quasistatic(direction);
}

frc2::CommandPtr ArmSubsystem::SysIdDynamic(frc2::sysid::Direction direction){
    return ArmSubsystem::m_sysIdRoutine.Dynamic(direction);
}


frc2::CommandPtr ArmSubsystem::ArmMethodCommand() {
  // Inline construction of command goes here.
  // Subsystem::RunOnce implicitly requires `this` subsystem.
  return RunOnce([/* this */] { /* one-time action goes here */ });
}

bool ArmSubsystem::ArmCondition() {
  // Query some boolean state, such as a digital sensor.
  return false;
}

void ArmSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
}

void ArmSubsystem::SimulationPeriodic() {
  // Implementation of subsystem simulation periodic method goes here.
}

void ArmSubsystem::TeleopMove(const double omega){
  
  m_armMotor1.Set(omega);

}

void ArmSubsystem::MoveToSetpoint(){
  m_armMotor1.SetControl(m_request.WithPosition(0.1_tr));
}

void ArmSubsystem::ConfigureHardware(){
  
  auto& baseArmConfigurator = m_armMotor1.GetConfigurator();

  configs::TalonFXConfiguration armMotorConfig{};
  baseArmConfigurator.Refresh(armMotorConfig);

  // Refresh allows the following static values to be configured and saved between intitializations
  // armMotorConfig.CurrentLimits.StatorCurrentLimitEnable;
  // armMotorConfig.CurrentLimits.StatorCurrentLimit = 40.0_A;
  // armMotorConfig.MotorOutput.NeutralMode.Coast;
  
  // m_armMotor1.GetConfigurator().Apply(armMotorConfig);
  // m_armMotor2.GetConfigurator().Apply(armMotorConfig);
  // m_armMotor3.GetConfigurator().Apply(armMotorConfig);
  // m_armMotor4.GetConfigurator().Apply(armMotorConfig);

  auto& slot0Configs = armMotorConfig.Slot0;
  slot0Configs.GravityType.Arm_Cosine;
  slot0Configs.kS = 0.0;
  slot0Configs.kV = 0.0;
  slot0Configs.kG = 0.0;
  slot0Configs.kA = 0.0;
  slot0Configs.kP = 0.0;
  slot0Configs.kI = 0.0;
  slot0Configs.kD = 0.0;

  auto& motionMagicConfigs = armMotorConfig.MotionMagic;
  motionMagicConfigs.MotionMagicCruiseVelocity = Constants::ARM_CRUISE_VELOCITY;
  motionMagicConfigs.MotionMagicAcceleration = Constants::ARM_MAX_ACCEL;
  motionMagicConfigs.MotionMagicJerk = Constants::ARM_TARGET_JERK;

  // motor config using rotor encoder values
  auto& armFeedback = armMotorConfig.Feedback;
  armFeedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::RotorSensor;
  armFeedback.SensorToMechanismRatio = Constants::GEAR_RATIO;

  // motor config with 1:1 CANCoder Values used
  // auto& armFeedback = armMotorConfig.Feedback;
  // armFeedback.FeedbackRemoteSensorID = m_armCANCoder.GetDeviceID()
  // armFeedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::RemoteCANcoder;
  // armFeedback.SensorToMechanismRatio = 1.0;

  // check the arm motor config stuff

  baseArmConfigurator.Apply(armMotorConfig);
  m_armMotor2.SetControl(controls::Follower{m_armMotor1.GetDeviceID(), false});
  m_armMotor3.SetControl(controls::Follower{m_armMotor1.GetDeviceID(), true});
  m_armMotor4.SetControl(controls::Follower{m_armMotor1.GetDeviceID(), true});

}