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

#include "propulsion/state_processor.hpp"

#include "propulsion/controller.hpp"

namespace hyped
{

namespace motor_control
{

StateProcessor::StateProcessor(int num_motors, Logger &log)
  : log_(log),
  sys_(System::getSystem()),
  data_(Data::getInstance()),
  num_motors_(num_motors),
  initialized_(false)
{
  controllers_ = new ControllerInterface*[num_motors_];

  log_.INFO("Motor", "Intializing motor controllers");
  for (int i = 0; i < num_motors_; i++) {
    controllers_[i] = new Controller(log_, i);
  }
}

void StateProcessor::initMotors()
{
  initialized_ = true;
}

void StateProcessor::accelerate()
{
  if (initialized_) {
    // Get the current motor RPM (this would normally be used to calculate target RPM)
    data::Motors motor_data = data_.getMotorData();
    for (int i = 0; i < num_motors_; i++) {
      motor_data.rpms[i] = controllers_[i]->getVelocity();
    }
    data_.setMotorData(motor_data);

    for (int i = 0;i < num_motors_; i++) {
      // Normally the speed would need to be ramped up in a very complicated way
      controllers_[i]->sendTargetVelocity(420);
    }
  } else {
    log_.INFO("Motor", "State Processor not initialized");
  }
}

void StateProcessor::quickStopAll()
{
  for (int i = 0;i < num_motors_; i++) {
    controllers_[i]->quickStop();
  }

  // Update the motor speeds in `Data`
  data::Motors motor_data = data_.getMotorData();
  for (int i = 0; i < num_motors_; i++) {
    motor_data.rpms[i] = controllers_[i]->getVelocity();
  }
  data_.setMotorData(motor_data);
}

bool StateProcessor::isInitialized()
{
  return this->initialized_;
}

}}  // namespace hyped::motor_control
