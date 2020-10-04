/*
 * Author: Neil McBlane, Brano Pilnan, Justus Rudolph
 * Organisation: HYPED
 * Date: 04/10/2020
 * Description: Main file for navigation class.
 *
 *    Copyright 2020 HYPED
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 *    except in compliance with the License. You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software distributed under
 *    the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 *    either express or implied. See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef NAVIGATION_NAVIGATION_HPP_
#define NAVIGATION_NAVIGATION_HPP_

#include <cstdint>

#include "data/data.hpp"
#include "data/data_point.hpp"
#include "sensors/imu.hpp"
#include "utils/logger.hpp"
#include "utils/math/integrator.hpp"

namespace hyped {

using data::Data;
using data::DataPoint;
using data::ModuleStatus;
using data::NavigationType;
using data::Sensors;
using utils::Logger;
using utils::math::Integrator;

namespace navigation {

class Navigation {
 public:
  /*
   * @brief Construct a new Navigation object
   *
   * @param log System logger
   * @param axis Axis used of acceleration measurements
   */
  explicit Navigation(Logger& log, unsigned int axis = 0);

  /*
   * @brief Get the current state of the navigation module
   *
   * @return ModuleStatus the current state of the navigation module
   */
  ModuleStatus getModuleStatus() const;

  /*
   * @brief Get the measured acceleration [m/s^2]
   *
   * @return NavigationType Returns the forward component of acceleration vector (negative when
   *                        decelerating) [m/s^2]
   */
  NavigationType getAcceleration() const;

  /*
   * @brief Get the measured velocity [m/s]
   *
   * @return NavigationType Returns the forward component of velocity vector [m/s]
   */
  NavigationType getVelocity() const;

  /*
   * @brief Get the measured displacement [m]
   *
   * @return NavigationType Returns the forward component of displacement vector [m]
   */
  NavigationType getDistance() const;

  /*
   * @brief Get the braking distance [m]
   *
   * @return NavigationType braking distance [m]
   */
  NavigationType getBrakingDistance() const;

  /*
   * @brief Update the central data structure
   */
  void updateData();

  /*
   * @brief Take acceleration readings from IMU, integrate and then update central data
   * structure with new values (i.e. the meat'n'potatoes of navigation).
   */
  void navigate();

 private:
  static constexpr NavigationType kDeceleration = 20;  // m/s^2

  // System communication
  Logger& log_;
  Data& data_;
  ModuleStatus status_;

  // counter for outputs
  unsigned int update_counter_;

  // To store estimated values
  DataPoint<NavigationType> acceleration_;
  DataPoint<NavigationType> velocity_;
  DataPoint<NavigationType> distance_;

  // To convert acceleration -> velocity -> distance
  Integrator<NavigationType> acceleration_integrator_;  // acceleration to velocity
  Integrator<NavigationType> velocity_integrator_;      // velocity to distance
};

}}  // namespace hyped::navigation

#endif  // NAVIGATION_NAVIGATION_HPP_
