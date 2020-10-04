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

#include "propulsion/controller.hpp"

namespace hyped {
namespace motor_control {

Controller::Controller(Logger& log, uint8_t id)
    : log_(log),
      velocity_(0)
{
}

void Controller::sendTargetVelocity(int32_t target_velocity)
{
  velocity_ = target_velocity;  // If only life was so simple...
}

void Controller::quickStop()
{
  // Send quickStop command
  velocity_ = 0;
}

int32_t Controller::getVelocity()
{
  // Normally, we would first need to send a message over CAN to tell the motor controller to send
  // us back the velocity. Once the reply would be received, it would be saved in the `velocity_`
  // variable and we would be able to retrieve it.
  return velocity_;
}

}}  // namespace hyped::motor_control
