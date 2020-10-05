/*
 * Author: HYPED
 * Organisation: HYPED
 * Date: 05/10/2020
 * Description: Main class for demo batteries
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

#include "sensors/batteries.hpp"

#include <random>

namespace hyped {

namespace sensors {

Batteries::Batteries(Logger& log) : log_(log)
{
}

void Batteries::getData(BatteryData* battery_data)
{
  static std::default_random_engine generator;
  static std::normal_distribution<float> distribution;
  battery_data->voltage             = int(234 + 10*distribution(generator));
  battery_data->charge              = int(50 + 5*distribution(generator));
  battery_data->average_temperature = int(30 + 5*distribution(generator));
}

bool Batteries::isOnline()
{
  return true;
}

}}  // namespace hyped::sensors
