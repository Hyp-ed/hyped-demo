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

#ifndef PROPULSION_MAIN_HPP_
#define PROPULSION_MAIN_HPP_

#include "data/data.hpp"
#include "state_processor.hpp"
#include "utils/concurrent/thread.hpp"
#include "utils/logger.hpp"

namespace hyped
{
using data::Data;
using data::State;
using utils::concurrent::Thread;
using utils::Logger;

namespace motor_control
{

class Main : public Thread
{
 public:
    Main(uint8_t id, Logger &log);

  /*
   * @brief This function is the entrypoint to the propulsion module and reacts to certain states
   */
  void run() override;

 private:
  Logger &log_;
  StateProcessor *state_processor_;
  Data& data_;
};

}  // namespace motor_control
}  // namespace hyped

#endif  // PROPULSION_MAIN_HPP_
