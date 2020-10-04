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

#include "brakes/brakes.hpp"

namespace hyped {

using data::ModuleStatus;

namespace brakes {

Brakes::Brakes(Logger& log)
    : log_(log),
      data_(data::Data::getInstance()),
      brakes_data_(data_.getBrakesData())
{
  brakes_data_.module_status = ModuleStatus::kReady;
  brakes_data_.engaged = false;
  data_.setBrakesData(brakes_data_);
}

void Brakes::engage()
{
  if (brakes_data_.engaged)
    return;
  log_.INFO("Brakes", "Engaging brakes");
  brakes_data_.engaged = true;
  data_.setBrakesData(brakes_data_);
}

void Brakes::disengage()
{
  if (!brakes_data_.engaged)
    return;
  log_.INFO("Brakes", "Disengaging brakes");
  brakes_data_.engaged = false;
  data_.setBrakesData(brakes_data_);
}

}}  // namespace hyped::embrakes
