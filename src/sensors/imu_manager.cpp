/*
 * Author: HYPED
 * Organisation: HYPED
 * Date: 03/10/2020
 * Description: IMU manager for getting IMU data from around the pod and pushes to data struct
 *
 *    Copyright 2019 HYPED
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


#include "sensors/imu_manager.hpp"

#include <chrono>
#include <thread>

#include "sensors/imu.hpp"
#include "utils/timer.hpp"
#include "utils/config.hpp"

namespace hyped {

using data::Data;
using data::Sensors;
using utils::System;
using utils::Timer;

namespace sensors {
ImuManager::ImuManager(Logger& log)
    : Thread(log),
      sys_(System::getSystem()),
      data_(Data::getInstance()),
      imu_ {nullptr}
{
  // Create IMU(s)
  imu_ = sys_.config->interfaceFactory.getImuInterfaceInstance();

  log_.INFO("IMU-MANAGER", "imu manager has been initialised");
}

void ImuManager::run()
{
  // Keep collecting data while the system is running
  while (sys_.running_) {
    imu_->getAccelerationX(&(imu_datapoint_.value));
    imu_datapoint_.timestamp = Timer::getTimeMicros();
    data_.setSensorsImuData(imu_datapoint_);

  // Add delay to simulate slow I/O
    std::this_thread::sleep_for(std::chrono::microseconds(500));
  }

  log_.INFO("IMU-MANAGER", "Thread shutting down");
}

}}  // namespace hyped::sensors
