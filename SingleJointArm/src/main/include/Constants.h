// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>
/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace Constants {

inline constexpr int kDriverControllerPort = 0;

inline constexpr double GEAR_RATIO = 1.0;
inline constexpr units::angular_velocity::turns_per_second_t ARM_CRUISE_VELOCITY{0.04}; //in RPS
inline constexpr units::angular_acceleration::turns_per_second_squared_t ARM_MAX_ACCEL{0.08}; // in RPS / S
inline constexpr units::angular_jerk::turns_per_second_cubed_t ARM_TARGET_JERK{0.8}; // in RPS / S / S


}  // namespace OperatorConstants
