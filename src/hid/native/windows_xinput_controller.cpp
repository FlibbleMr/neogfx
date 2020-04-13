// windows_xinput_controller.cpp
/*
  neogfx C++ GUI Library
  Copyright (c) 2020 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <neogfx/neogfx.hpp>
#include "windows_xinput_controller.hpp"

namespace neogfx
{
    namespace native::windows
    {
        xinput_controller::xinput_controller(IDirectInputDevice8* aDevice,  hid_device_subclass aSubclass, hid_device_uuid aProductId, hid_device_uuid aInstanceId) :
            game_controller{ aSubclass, aProductId, aInstanceId }, iDevice{ aDevice }
        {
        }

        xinput_controller::~xinput_controller()
        {
            iDevice->Release();
        }

        bool xinput_controller::is_button_pressed(game_controller_button_index aButtonIndex) const
        {
            throw std::logic_error("not yet implemented");
        }

        bool xinput_controller::is_button_pressed(game_controller_button aButton) const
        {
            throw std::logic_error("not yet implemented");
        }

        double xinput_controller::left_trigger_position() const
        {
            throw std::logic_error("not yet implemented");
        }

        double xinput_controller::right_trigger_position() const
        {
            throw std::logic_error("not yet implemented");
        }

        const vec2& xinput_controller::left_thumb_position() const
        {
            throw std::logic_error("not yet implemented");
        }

        const vec2& xinput_controller::right_thumb_position() const
        {
            throw std::logic_error("not yet implemented");
        }

        const vec3& xinput_controller::stick_position() const
        {
            throw std::logic_error("not yet implemented");
        }

        const vec3& xinput_controller::stick_rotation() const
        {
            throw std::logic_error("not yet implemented");
        }

        const vec2& xinput_controller::slider_position() const
        {
            throw std::logic_error("not yet implemented");
        }
    }
}