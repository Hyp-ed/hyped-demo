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
#ifndef NAVIGATION_MAIN_HPP_
#define NAVIGATION_MAIN_HPP_

#include "data/data.hpp"
#include "navigation/navigation.hpp"
#include "utils/concurrent/thread.hpp"
#include "utils/logger.hpp"
#include "utils/system.hpp"

namespace hyped {

using utils::concurrent::Thread;
using utils::System;
using utils::Logger;

namespace navigation {

class Main: public Thread {
 public:
  explicit Main(uint8_t id, Logger& log);
  void run() override;

 private:
  Logger& log_;
  System& sys_;
  Navigation nav_;
};

}}  // namespace hyped::navigation

#endif  // NAVIGATION_MAIN_HPP_
