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

#ifndef PROPULSION_STATE_PROCESSOR_INTERFACE_HPP_
#define PROPULSION_STATE_PROCESSOR_INTERFACE_HPP_

#include "utils/logger.hpp"
#include "utils/system.hpp"

namespace hyped
{

namespace motor_control
{

using utils::Logger;
using utils::System;

class StateProcessorInterface
{
 public:
  /*
   * @brief { Sends the desired settings to the motors }
   */
  virtual void initMotors() = 0;

  /*
   * @brief { Stops all motors }
   */
  virtual void quickStopAll() = 0;

  /*
   * @brief { Tells the controllers to start accelerating the motors }
   */
  virtual void accelerate() = 0;

  /*
   * @brief { Returns if the motors are initialised already }
   */
  virtual bool isInitialized() = 0;
};

}  // namespace motor_control
}  // namespace hyped

#endif  // PROPULSION_STATE_PROCESSOR_INTERFACE_HPP_
