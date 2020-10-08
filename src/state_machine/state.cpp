
/*
 * Authors: Kornelija Sukyte
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
#include "state_machine/state.hpp"

namespace hyped {

namespace state_machine {

State::State(Logger& log, Main* state_machine)
  : log_(log),
    data_(data::Data::getInstance()),
    state_machine_(state_machine)
{}

void State::checkEmergencyStop()
{
  telemetry_data_ = data_.getTelemetryData();
  sm_data_        = data_.getStateMachineData();

  if (telemetry_data_.emergency_stop_command) {
    log_.ERR("STATE", "STOP command received");
    telemetry_data_.emergency_stop_command = false;
    data_.setTelemetryData(telemetry_data_);

    sm_data_.current_state = data::State::kFinished;
    data_.setStateMachineData(sm_data_);

    state_machine_->current_state_ = state_machine_->finished_;
  }
}

// Idle state

void Idle::transitionCheck()
{
  telemetry_data_ = data_.getTelemetryData();
  sm_data_        = data_.getStateMachineData();

  if (telemetry_data_.launch_command) {
    log_.INFO("STATE", "launch command received");
    telemetry_data_.launch_command = false;
    data_.setTelemetryData(telemetry_data_);
    log_.DBG("STATE", "launch command cleared");

    sm_data_.current_state = data::State::kAccelerating;
    data_.setStateMachineData(sm_data_);

    state_machine_->current_state_ = state_machine_->accelerating_;
    log_.DBG("STATE", "Transitioned to 'Accelerating'");
  }
}

// Accelerating state

void Accelerating::transitionCheck()
{
  nav_data_       = data_.getNavigationData();
  sm_data_        = data_.getStateMachineData();
  telemetry_data_ = data_.getTelemetryData();

  if (nav_data_.distance +
    nav_data_.braking_distance +
    20 >= telemetry_data_.run_length) {
    log_.INFO("STATE", "max distance reached");
    log_.INFO("STATE", "current distance: %fm, braking distance: %fm",
              nav_data_.distance, nav_data_.braking_distance);

    sm_data_.current_state = data::State::kNominalBraking;
    data_.setStateMachineData(sm_data_);

    state_machine_->current_state_ = state_machine_->nominal_braking_;
  }
}

// Nominal braking state

void NominalBraking::transitionCheck()
{
  nav_data_       = data_.getNavigationData();
  brakes_data_    = data_.getBrakesData();
  sm_data_        = data_.getStateMachineData();

  log_.DBG3("STATE", "Waiting for the pod to stop. Current velocity: %fm/s", nav_data_.velocity);
  if (nav_data_.velocity >= -0.1 && nav_data_.velocity <= 0.1
    && brakes_data_.engaged) {
    log_.INFO("STATE", "Velocity reached zero.");

    sm_data_.current_state = data::State::kFinished;
    data_.setStateMachineData(sm_data_);

    state_machine_->current_state_ = state_machine_->finished_;
  }
}

// Finished state

void Finished::transitionCheck()
{
  telemetry_data_ = data_.getTelemetryData();
  sm_data_        = data_.getStateMachineData();

  if (telemetry_data_.reset_command) {
    log_.INFO("STATE", "reset command received");
    telemetry_data_.reset_command = false;  // reset the command to false
    data_.setTelemetryData(telemetry_data_);

    sm_data_.current_state = data::State::kIdle;
    data_.setStateMachineData(sm_data_);

    state_machine_->current_state_ = state_machine_->idle_;
  }
}

}  // namespace state_machine
}  // namespace hyped
