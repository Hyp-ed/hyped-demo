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

#include "navigation/navigation.hpp"

namespace hyped {
namespace navigation {

Navigation::Navigation(Logger& log, unsigned int axis/*=0*/)
    : log_(log),
      data_(Data::getInstance()),
      status_(ModuleStatus::kStart),
      update_counter_(0),
      acceleration_(0, 0.),
      velocity_(0, 0.),
      distance_(0, 0.),
      acceleration_integrator_(&velocity_),
      velocity_integrator_(&distance_)
{
  log_.INFO("NAV", "Navigation module started");
  status_ = ModuleStatus::kInit;
  updateData();
  log_.INFO("NAV", "Navigation module initialised");
}

ModuleStatus Navigation::getModuleStatus() const
{
  return status_;
}

NavigationType Navigation::getAcceleration() const
{
  return acceleration_.value;
}

NavigationType Navigation::getVelocity() const
{
  return velocity_.value;
}

NavigationType Navigation::getDistance() const
{
  return distance_.value;
}

NavigationType Navigation::getBrakingDistance() const
{
  NavigationType v = getVelocity();
  return v*v / (2*kDeceleration);
}

void Navigation::navigate()
{
  DataPoint<data::ImuData> sensor_readings = data_.getSensorsImuData();

  log_.DBG1("NAV", "Raw acceleration: %.3f", sensor_readings.value.acc_x);

  acceleration_.value = sensor_readings.value.acc_x;
  acceleration_.timestamp = sensor_readings.timestamp;

  acceleration_integrator_.update(acceleration_);
  velocity_integrator_.update(velocity_);

  updateData();
}

void Navigation::updateData()
{
  data::Navigation nav_data;
  nav_data.module_status    = getModuleStatus();
  nav_data.distance         = getDistance();
  nav_data.velocity         = getVelocity();
  nav_data.acceleration     = getAcceleration();
  nav_data.braking_distance = getBrakingDistance();
  data_.setNavigationData(nav_data);

  // Print some info every 1000 updates
  if (update_counter_ % 1000 == 0) {
    log_.DBG("NAV", "%d: Data Update: a=%.3f, v=%.3f, d=%.3f",
               update_counter_, nav_data.acceleration, nav_data.velocity, nav_data.distance);
  }
  update_counter_++;
}

}}  // namespace hyped::navigation
