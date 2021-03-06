/*
* Author: Kornelija Sukyte, Branislav Pilnan
* Organisation: HYPED
* Date: 04/10/2020
* Description:
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

#ifndef BRAKES_BRAKES_HPP_
#define BRAKES_BRAKES_HPP_

#include "utils/timer.hpp"
#include "utils/logger.hpp"
#include "utils/system.hpp"
#include "utils/concurrent/thread.hpp"
#include "data/data.hpp"

namespace hyped {

using utils::concurrent::Thread;
using utils::Logger;
using data::ModuleStatus;

namespace brakes {

class Brakes {
 public:
  /**
   * @brief Construct a new Brakes object
   *
   * @param log, node id
   */
  explicit Brakes(Logger& log);

  /**
   * @brief Ensures the brakes are engaged and updates the braking force
   */
  void engage();

  /**
   * @brief Ensures the brakes are disengaged and updates the braking force
   */
  void disengage();

 private:
  utils::Logger& log_;
  data::Data&    data_;
  data::Brakes   brakes_data_;
};

}}  // namespace hyped::embrakes

#endif  // BRAKES_BRAKES_HPP_
