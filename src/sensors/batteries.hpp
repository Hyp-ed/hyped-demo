/*
 * Author: HYPED
 * Organisation: HYPED
 * Date: 05/10/2020
 * Description: Main class for demo BMS (Battery Management System) driver
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

#ifndef SENSORS_BATTERIES_HPP_
#define SENSORS_BATTERIES_HPP_

#include "sensors/interface.hpp"
#include "utils/logger.hpp"

namespace hyped {

using utils::Logger;

namespace sensors {


class Batteries : public BMSInterface {
 public:
  /*
   * @brief Construct a new Batteries object
   *
   * @param log=
   */
  explicit Batteries(Logger& log);

  /*
   * @brief Generates random battery stats
   * @param[out] battery_data BatteryData output pointer
   */
  void getData(BatteryData* battery_data) override;
  bool isOnline() override;

 private:
  utils::Logger& log_;
};

}}    // namespace hyped::sensors

#endif  // SENSORS_BATTERIES_HPP_
