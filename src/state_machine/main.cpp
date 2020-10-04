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
    data_(data::Data::getInstance()),
	  sm_data_(data_.getStateMachineData())
{}

/**
  *  @brief  Runs state machine thread.
  */

void Main::run()
{
  utils::System& sys = utils::System::getSystem();

	current_state_ = new State(log_, this); // pointer to current state object
	current_state_ = &idle_;

	sm_data_.current_state = data::State::kIdle; // Current state in data structure

  while (sys.running_) {

		current_state_->checkEmergencyStop();
		current_state_->TransitionCheck();

	}
}

}  // namespace state_machine
}  // namespace hyped