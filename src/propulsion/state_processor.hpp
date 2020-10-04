/*
 * Author: Gregor Konzett, Branislav Pilnan
 * Organisation: HYPED
 * Date: 04/10/2020
 * Description: Handles the different states of the state machine
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

#ifndef PROPULSION_STATE_PROCESSOR_HPP_
#define PROPULSION_STATE_PROCESSOR_HPP_

#include "data/data.hpp"
#include "propulsion/controller_interface.hpp"
#include "propulsion/state_processor_interface.hpp"
#include "utils/logger.hpp"
#include "utils/system.hpp"

namespace hyped
{

namespace motor_control
{

using data::Data;
using utils::Logger;
using utils::System;

class StateProcessor : public StateProcessorInterface
{
 public:
  /*
   * @brief {Initializes the state processors with the amount of motors and the logger}
   * */
  StateProcessor(int num_motors, Logger &log);

  /*
   * @brief { Sends the desired settings to the motors }
   */
  void initMotors() override;

  /*
   * @brief { Stops all motors }
   */
  void quickStopAll() override;

  /*
   * @brief { Tells the controllers to start accelerating the motors }
   */
  void accelerate() override;

  /*
   * @brief { Returns if the motors are initialised already }
   */
  bool isInitialized() override;

 private:
  Logger &log_;
  System &sys_;
  Data   &data_;
  int num_motors_;
  bool initialized_;
  ControllerInterface** controllers_;
};

}}  // namespace hyped::motor_control

#endif  // PROPULSION_STATE_PROCESSOR_HPP_
