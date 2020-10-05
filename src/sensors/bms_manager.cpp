/*
 * Author: HYPED
 * Organisation: HYPED
 * Date: 20/06/18
 * Description:
 * BMS manager for getting battery data and pushes to data struct.
 * Checks whether batteries are in range and enters emergency state if fails.
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


#include "sensors/bms_manager.hpp"

#include "sensors/batteries.hpp"
#include "utils/config.hpp"

namespace hyped {

using data::ModuleStatus;

namespace sensors {

BmsManager::BmsManager(Logger& log)
    : Thread(log),
      sys_(utils::System::getSystem()),
      data_(Data::getInstance())
{
  for (int i = 0; i < bms_.size(); i++) {
    bms_[i] = new Batteries(log_);
  }

  // kInit for SM transition
  batteries_ = data_.getBatteriesData();
  batteries_.module_status = data::ModuleStatus::kInit;
  data_.setBatteriesData(batteries_);
  Thread::yield();
  log_.INFO("BMS-MANAGER", "batteries data has been initialised");
}

void BmsManager::run()
{
  while (sys_.running_) {
    // keep updating data_ based on values read from sensors
    for (int i = 0; i < data::Batteries::kNumBatteries; i++) {
      bms_[i]->getData(&(batteries_.readings[i]));
    }

    if (batteries_.module_status == ModuleStatus::kInit)
      batteries_.module_status = ModuleStatus::kReady;

    if (!batteriesInRange())
      batteries_.module_status = ModuleStatus::kCriticalFailure;

    // publish the new data
    data_.setBatteriesData(batteries_);

    Thread::sleep(1000);
  }
}

bool BmsManager::batteriesInRange()
{
  // check LP
  for (int i = 0; i < data::Batteries::kNumBatteries; i++) {
    auto& battery = batteries_.readings[i];      // reference batteries individually
    if (battery.voltage < 175 || battery.voltage > 294) {   // voltage in 17.5V to 29.4V
      log_.ERR("BMS-MANAGER", "BMS %d voltage out of range: %d", i, battery.voltage);
      return false;
    }

    if (battery.average_temperature < 10 || battery.average_temperature > 60) {
      log_.ERR("BMS-MANAGER", "BMS %d temperature out of range: %d",
               i, battery.average_temperature);
      return false;
    }

    if (battery.charge < 20 || battery.charge > 100) {  // charge in 20% to 100%
      log_.ERR("BMS-MANAGER", "BMS %d charge out of range: %d", i, battery.charge);
      return false;
    }
  }
  return true;
}

}}  // namespace hyped::sensors
