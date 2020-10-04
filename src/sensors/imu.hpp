/*
 * Author: Branislav Pilnan
 * Organisation: HYPED
 * Date: 03/10/2020
 * Description: Defines the IMU class - a sensor driver for "measuring" acceleration
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

#ifndef SENSORS_IMU_HPP_
#define SENSORS_IMU_HPP_

#include <vector>

#include "sensors/interface.hpp"
#include "utils/logger.hpp"

namespace hyped {

using utils::Logger;
using data::Data;

namespace sensors {

/*
 * @brief An extremely simplified version of an IMU sensor.
 *
 * A real sensor driver would be *much* more complicated, handling a lot of communication with the
 * actual hardware sensor. IMUs usually require a complex series of instructions only to be started
 * up and configured. Getting the data from them also requires a fair bit of code.
 */
class Imu : public ImuInterface {
 public:
  Imu(Logger& log);
  /*
   *  @brief Returns if the sensor is online
   *
   *  @return true if the sensor is online
   */
  bool isOnline() override;
  /*
   *  @brief Get the forward acceleration and update the pointer
   *
   * This simplified version just returns some constants based on whether the pod is currently
   * accelerating or decelerating.
   */
  void getAccelerationX(ImuData* data) override;

 private:
  Logger& log_;
  Data&   data_;
  bool    is_online_;
};

}}  // namespace hyped::sensors


#endif  // SENSORS_IMU_HPP_
