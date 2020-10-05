/*
 * Author:Kornelija Sukyte
 * Organisation: HYPED
 * Date:
 * Description:
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
#include <cstdint>

#include "state_machine/main.hpp"

namespace hyped {
namespace state_machine {

Main::Main(uint8_t id, Logger& log)
  : Thread(id, log),
    sys_(utils::System::getSystem()),
    data_(data::Data::getInstance())
{}

/**
  *  @brief  Runs state machine thread.
  */

void Main::run()
{
  utils::System& sys = utils::System::getSystem();

  idle_ = new Idle(log_, this); // constructing state object for Idle
  accelerating_ = new Accelerating(log_, this); // constructing state object for Accelerating
  nominal_braking_ = new NominalBraking(log_, this); // constructing state object for Nominal braking
  finished_ = new Finished(log_, this); // constructing state object for Finished

  current_state_ = idle_; // set current state to point to Idle

  sm_data_.current_state = data::State::kIdle; // s et current state in data structure

  while (sys.running_) {

    telemetry_data_ = data_.getTelemetryData();
    nav_data_       = data_.getNavigationData();
    sm_data_        = data_.getStateMachineData();
    motor_data_     = data_.getMotorData();
    batteries_data_ = data_.getBatteriesData();
    sensors_data_   = data_.getSensorsData();
    brakes_data_    = data_.getBrakesData();

    current_state_->checkEmergencyStop();
    current_state_->TransitionCheck();

  }
}

}  // namespace state_machine
}  // namespace hyped
