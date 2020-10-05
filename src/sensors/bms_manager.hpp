/*
 * Author: HYPED
 * Organisation: HYPED
 * Date: 05/10/2020
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

#ifndef SENSORS_BMS_MANAGER_HPP_
#define SENSORS_BMS_MANAGER_HPP_

#include <array>
#include <cstdint>

#include "data/data.hpp"
#include "utils/concurrent/thread.hpp"

#include "sensors/interface.hpp"
#include "utils/system.hpp"

using std::array;

namespace hyped {

using data::BatteryData;
using utils::Logger;
using utils::concurrent::Thread;

namespace sensors {

class BmsManager: public Thread  {
 public:
  explicit BmsManager(Logger& log);
  void run() override;

 private:
  /**
   * @brief checks voltage, current, temperature, and charge
   */
  bool batteriesInRange();

  array<BMSInterface*, data::Batteries::kNumBatteries> bms_;
  utils::System&                                       sys_;
  data::Data&                                          data_;

  /**
   * @brief holds BatteryData and module_status
   */
  data::Batteries batteries_;
};

}}  // namespace hyped::sensors

#endif  // SENSORS_BMS_MANAGER_HPP_
