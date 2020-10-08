/*
* Author: Kornelija Sukyte, Branislav Pilnan
* Organisation: HYPED
* Date: 03/10/2020
* Description: Entrypoint class to the brakes module, started in it's own thread.
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

#include "main.hpp"
#include "utils/config.hpp"

namespace hyped {

using data::State;
using utils::System;

namespace brakes {

Main::Main(uint8_t id, Logger &log)
  : Thread(id, log),
    log_(log),
    data_(data::Data::getInstance()),
    brakes_(log_)
{
}

void Main::run()
{
  log_.INFO("Brakes", "Thread started");

  System& sys = System::getSystem();

  while (sys.running_) {
    // Get the current state of embrakes and state machine modules from data
    data::StateMachine sm_data = data_.getStateMachineData();

    if (sm_data.current_state == State::kNominalBraking ||
        sm_data.current_state == State::kEmergencyBraking) {
      brakes_.engage();
    } else {
      brakes_.disengage();
    }
  }

  log_.INFO("Brakes", "Thread shutting down");
}

}  // namespace embrakes
}  // namespace hyped
