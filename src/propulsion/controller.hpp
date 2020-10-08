/*
 * Author: Iain Macpherson, Branislav Pilnan
 * Organisation: HYPED
 * Date: 04/10/2020
 * Description: Main class for the Motor Controller
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

#ifndef PROPULSION_CONTROLLER_HPP_
#define PROPULSION_CONTROLLER_HPP_

#include "data/data.hpp"
#include "propulsion/controller_interface.hpp"
#include "utils/logger.hpp"
#include "utils/system.hpp"


namespace hyped {

using utils::Logger;

namespace motor_control {

class Controller : public ControllerInterface {
 public:
  /*
   * @brief Construct a new Controller object
   * @param log
   * @param id
   */
  Controller(Logger& log, uint8_t id);

  /*
   * @brief Send the target velocity to the motor controller.
   * @param target_velocity - in rpm (calculated in speed calculator)
   */
  void sendTargetVelocity(int32_t target_velocity) override;

  /*
   * @brief Send a request to the motor controller to get the actual velocity
   */
  int32_t getVelocity() override;

  /*
   * @brief Set the controller to quickstop mode.
   */
  void quickStop() override;

 private:
  Logger& log_;
  int32_t velocity_;
};

}}  // namespace hyped::motor_control

#endif  // PROPULSION_CONTROLLER_HPP_
