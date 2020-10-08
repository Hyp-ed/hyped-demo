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

#ifndef BRAKES_MAIN_HPP_
#define BRAKES_MAIN_HPP_

#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"
#include "utils/logger.hpp"
#include "data/data.hpp"

#include "brakes/brakes.hpp"

namespace hyped {

using utils::concurrent::Thread;
using utils::Logger;
using data::ModuleStatus;

namespace brakes {
/*
 * @description This module handles the interaction with the embrakes.
*/
class Main : public Thread
{
  public:
    /*
    * @brief Initialises essential variables
    */
    Main(uint8_t id, Logger &log);

    /*
    * @brief Checks for braking states to engage the brakes
    */
    void run() override;

  private:
    Logger&     log_;
    data::Data& data_;
    Brakes      brakes_;
};

}}  // namespace hyped::embrakes

#endif  // BRAKES_MAIN_HPP_
