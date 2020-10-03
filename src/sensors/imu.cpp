/*
 * Author: Branislav Pilnan, Martin Kristien
 * Organisation: HYPED
 * Date: 03/10/2020
 * Description: Implementation of an oversimplified demo IMU "driver"
 *
 *    Copyright 2020 HYPED
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#include <algorithm>
#include <vector>

#include "sensors/imu.hpp"
#include "utils/interface_factory.hpp"


namespace hyped {
namespace sensors {

Imu::Imu(Logger& log)
    : log_(log),
    is_online_(true)
{
  log_.INFO("Imu", "Created an IMU sensor");
}

bool Imu::isOnline()
{
  return is_online_;
}

void Imu::getAccelerationX(ImuData* data)
{
  // TODO(Brano): get current force from motors and brakes
  // TODO(Brano): get pod mass
  // TODO(Brano): calculate acceleration and update data
}

namespace {
ImuInterface* createImu()
{
  Logger log(true, -1);
  return new Imu(log);
}

int regImu = utils::InterfaceFactory<ImuInterface>::registerCreator("Imu", createImu);
}   // namespace ::

}}  // namespace hyped::sensors
