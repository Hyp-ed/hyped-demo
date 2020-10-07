/*
 * Author: Lukas Schaefer, Neil McBlane, Branislav Pilnan
 * Organisation: HYPED
 * Date: 04/10/2020
 * Description: Main file for navigation class.
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

#include "navigation/main.hpp"

namespace hyped {

using data::Data;
using data::State;

namespace navigation {

Main::Main(uint8_t id, Logger& log)
    : Thread(id, log),
      log_(log),
      sys_(System::getSystem()),
      nav_(log, sys_.axis) {}

void Main::run()
{
  log_.INFO("NAV", "Axis: %d", sys_.axis);
  log_.INFO("NAV", "Navigation waiting for calibration");

  Data& data = Data::getInstance();
  bool navigation_complete = false;

  // wait for calibration state for calibration
  while (sys_.running_ && !navigation_complete) {
    State current_state = data.getStateMachineData().current_state;

    switch (current_state) {
      case State::kIdle :
      case State::kReady :
        break;
      case State::kCalibrating :
        break;
      case State::kAccelerating :
      case State::kNominalBraking :
      case State::kEmergencyBraking :
      case State::kExiting :
      case State::kRunComplete :
        nav_.navigate();
        break;
      default :
        navigation_complete = true;
        log_.INFO("NAV", "Navigation complete");
        break;
    }
    Thread::yield();
  }

  log_.INFO("NAV", "Thread shutting down");
}

}}  // namespace hyped::navigation
