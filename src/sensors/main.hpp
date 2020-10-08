/*
 * Author: HYPED
 * Organisation: HYPED
 * Date: 03/10/2020
 * Description:
 * Main initialises and manages sensor drivers. Main is not responsible for initialisation
 * of supporting io drivers (spi, can, adc). This should be done by the sensor
 * drivers themselves.
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

#ifndef SENSORS_MAIN_HPP_
#define SENSORS_MAIN_HPP_

#include <cstdint>

#include "sensors/interface.hpp"
#include "bms_manager.hpp"
#include "imu_manager.hpp"
#include "utils/system.hpp"

namespace hyped {

namespace sensors {

/**
 * @brief Initialise sensors, data instances to be pulled in managers
 *        gpio threads and adc checks declared in main
 */
class Main: public Thread {
 public:
  Main(uint8_t id, utils::Logger& log);
  void run() override;    // from thread

 private:
  data::Data&     data_;
  utils::System&  sys_;
  utils::Logger&  log_;

  // master data structures
  data::Sensors   sensors_;
  data::Batteries batteries_;

  ImuManager*     imu_manager_;
  BmsManager*     battery_manager_;
  bool            log_error_ = false;
};

}}  // namespace hyped::sensors

#endif  // SENSORS_MAIN_HPP_
