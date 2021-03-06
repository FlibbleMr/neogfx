// script_widget.hpp
/*
  neoGFX Design Studio
  Copyright(C) 2021 Leigh Johnston
  
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
#include <neogfx/gui/window/window.hpp>
#include <neogfx/gui/widget/text_edit.hpp>
#include <neogfx/tools/DesignStudio/i_element.hpp>
#include <neogfx/tools/DesignStudio/script.hpp>

namespace neogfx::DesignStudio
{
    class script_widget : public window
    {
        typedef window base_type;
    public:
        script_widget(i_widget& aParent, window_style aStyle) :
            window{ aParent, aStyle },
            iEditor{ client_layout() }
        {
            set_padding(neogfx::padding{ 2.0_dip, 2.0_dip, 2.0_dip, 2.0_dip });
            set_minimum_size(size{ 128.0_dip, 128.0_dip });
        }
    private:
        text_edit iEditor;
        sink iSink;
    };

    template <>
    struct element_traits<script_widget> : element_traits<i_element>
    {
        typedef script base;
        static constexpr bool needsCaddy = false;
    };
}
