/*
 * Author: Gregor Konzett, Branislav Pilnan
 * Organisation: HYPED
 * Date: 04/10/2020
 * Description: Main entrypoint to a demo motor control module
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

#include "propulsion/main.hpp"

namespace hyped
{

using data::ModuleStatus;

namespace motor_control
{
Main::Main(uint8_t id, Logger &log)
  : Thread(id, log),
    log_(log),
    state_processor_(new StateProcessor(data::Motors::kNumMotors, log)),
    data_(Data::getInstance())
{
}

void Main::run()
{
  log_.INFO("Motor", "Thread started");

  System &sys = System::getSystem();

  data::Motors motor_data = data_.getMotorData();

  bool is_running = true;
  while (is_running && sys.running_) {
    // Get the current state of the system from the state machine's data
    data::State current_state = data_.getStateMachineData().current_state;

    if (current_state == State::kIdle) {  // Initialize motors
      if (motor_data.module_status != ModuleStatus::kInit) {
        motor_data.module_status = ModuleStatus::kInit;
        data_.setMotorData(motor_data);
        state_processor_->initMotors();
      }
    } else if (current_state == State::kCalibrating) {
      if (state_processor_->isInitialized() && motor_data.module_status != ModuleStatus::kReady) {
        motor_data.module_status = ModuleStatus::kReady;
        data_.setMotorData(motor_data);
      }
    } else if (current_state == State::kReady) {
      // Standby and wait

      // We got rid of kIdle for demo so init motors here:
      state_processor_->initMotors();
    } else if (current_state == State::kAccelerating) {
      // Accelerate the motors
      state_processor_->accelerate();
    } else if (current_state == State::kNominalBraking ||
               current_state == State::kEmergencyBraking) {
      // Stop all motors
      state_processor_->quickStopAll();
    } else if (current_state == State::kExiting) {
      // Move very slowly out of tube
    } else if (current_state == State::kFailureStopped) {
      // Enter preoperational
    } else if (current_state == State::kFinished) {
    } else if (current_state == State::kRunComplete) {
      // Run complete
      state_processor_->quickStopAll();
    } else {
      // Unknown State
      is_running = false;
      log_.ERR("Motor", "Unknown state");
      motor_data.module_status = ModuleStatus::kCriticalFailure;
      data_.setMotorData(motor_data);
      state_processor_->quickStopAll();
    }
    sleep(1);
  }

  log_.INFO("Motor", "Thread shutting down");
}
}  // namespace motor_control
}  // namespace hyped
