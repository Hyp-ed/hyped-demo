/*
 * Author: HYPED
 * Organisation: HYPED
 * Date: 03/10/2020
 * Description: IMU manager for getting IMU data from around the pod and push it to data struct
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

#ifndef SENSORS_IMU_MANAGER_HPP_
#define SENSORS_IMU_MANAGER_HPP_

#include <cstdint>

#include "data/data.hpp"
#include "sensors/interface.hpp"
#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"

namespace hyped {

using data::DataPoint;
using utils::Logger;
using utils::concurrent::Thread;

namespace sensors {
/**
 * @brief A class to operate several IMU sensors. Currently, it only handles a single IMU.
 */
class ImuManager: public Thread {
 public:
  /**
   * @brief Construct a new Imu Manager object
   *
   * @param log
   */
  explicit ImuManager(Logger& log);

  /**
   * @brief Calibrate IMUs then begin collecting data.
   */
  void run() override;

 private:
  utils::System& sys_;

  /**
   * @brief needs to be references because run() passes directly to data struct
   */
  data::Data& data_;

  /**
   * @brief DataPoint array for all kNumImus
   */
  DataPoint<ImuData> imu_datapoint_;

  ImuInterface* imu_;
};

}}  // namespace hyped::sensors

#endif  // SENSORS_IMU_MANAGER_HPP_
