/*
 * Author: Uday Patel, Jack Horsburgh and Ragnor Comerford
 * Organisation: HYPED
 * Date: 03/10/2020
 * Description: Main sensor interfaces, used to create real and fake sensors
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

#ifndef SENSORS_INTERFACE_HPP_
#define SENSORS_INTERFACE_HPP_

#include <string>

#include "data/data.hpp"

namespace hyped {

using data::ImuData;
using data::BatteryData;

namespace sensors {

class SensorInterface {
 public:
  /**
   * @brief Check if sensor is responding, i.e. connected to the system
   * @return true - if sensor is online
   */
  virtual bool isOnline() = 0;
};

class ImuInterface: public SensorInterface {
 public:
  /**
   * @brief Get IMU data
   * @param imu - output pointer to be filled by this sensor
   */
  virtual void getAccelerationX(ImuData* imu) = 0;
};

class BMSInterface: public SensorInterface {  // BMS = Battery Management System
 public:
  /**
   * @brief Get Battery data
   * @param battery_data - output pointer to be filled by this sensor
   */
  virtual void getData(BatteryData* battery_data) = 0;
};

}}  // namespace hyped::sensors

#endif  // SENSORS_INTERFACE_HPP_
