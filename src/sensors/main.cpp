/*
 * Author: HYPED
 * Organisation: HYPED
 * Date: 03/10/2020
 * Description:
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

#include "sensors/main.hpp"

#include "utils/config.hpp"

namespace hyped {

using data::Data;
using data::Sensors;
using utils::concurrent::Thread;
using utils::System;

namespace sensors {

Main::Main(uint8_t id, utils::Logger& log)
  : Thread(id, log),
    data_(data::Data::getInstance()),
    sys_(utils::System::getSystem()),
    log_(log),
    imu_manager_(new ImuManager(log)),
    battery_manager_(new BmsManager(log))
{
  // kInit for SM transition
  sensors_ = data_.getSensorsData();
  sensors_.module_status = data::ModuleStatus::kInit;
  data_.setSensorsData(sensors_);
  log_.INFO("SNS", "Sensors have been initialised");
}

void Main::run()
{
  // start all managers
  battery_manager_->start();
  imu_manager_->start();

  while (sys_.running_) {
    // Could check temperature or other sensors here
    Thread::yield();
  }

  imu_manager_->join();
  battery_manager_->join();
  log_.INFO("SNS", "Main thread shutting down");
}

}}  // namespace hyped::sensors
