// i_hid_device.hpp
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
#include <neolib/uuid.hpp>
#include <neogfx/core/event.hpp>

namespace neogfx
{
    enum class hid_device_type : uint32_t
    {
        Input,
        Output
    };

    enum class hid_device_class : uint32_t
    {
        Keyboard,
        Mouse,
        GameController,
        Unknown
    };

    enum class hid_device_subclass : uint32_t
    {
        Keyboard,
        Keypad,
        Mouse,
        Touchpad,
        Touchscreen,
        Joystick,
        Gamepad,
        Unknown
    };

    typedef neolib::uuid hid_device_class_uuid;

    class i_hid_device
    {
    public:
        declare_event(enabled)
        declare_event(disabled)
    public:
        virtual ~i_hid_device() = default;
    public:
        virtual hid_device_type device_type() const = 0;
        virtual hid_device_class device_class() const = 0;
        virtual hid_device_subclass device_subclass() const = 0;
        virtual const i_string& device_name() const = 0;
        virtual bool is_enabled() const = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;
    };
}