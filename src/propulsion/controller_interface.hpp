/*
 * Author: George Karabassis, Iain Macpherson, Branislav Pilnan
 * Organisation: HYPED
 * Date: 04/10/2020
 * Description: Interface for controller classes
 *
 *    Copyright 2019 HYPED
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

#ifndef PROPULSION_CONTROLLER_INTERFACE_HPP_
#define PROPULSION_CONTROLLER_INTERFACE_HPP_

#include <stdint.h>

namespace hyped
{

namespace motor_control
{
enum ControllerState {
  kNotReadyToSwitchOn,
  kSwitchOnDisabled,
  kReadyToSwitchOn,
  kSwitchedOn,
  kOperationEnabled,
  kQuickStopActive,
  kFaultReactionActive,
  kFault,
};

class ControllerInterface {
 public:
  virtual void sendTargetVelocity(int32_t target_velocity) = 0;
  virtual int32_t getVelocity() = 0;
  virtual void quickStop() = 0;
};
}  // namespace motor_control
}  // namespace hyped

#endif  // PROPULSION_CONTROLLER_INTERFACE_HPP_
