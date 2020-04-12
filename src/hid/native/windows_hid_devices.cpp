// windows_hid_devices.cpp
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
#include <Dbt.h>
#include <initguid.h>
#include <Usbiodef.h>
#include "windows_hid_devices.hpp"

namespace neogfx
{
    namespace native::windows
    {
        LRESULT hid_helper_wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message) 
            {
            case WM_DEVICECHANGE:
                switch (wParam) 
                {
                case DBT_DEVICEARRIVAL:
                case DBT_DEVICEREMOVECOMPLETE:
                    if (reinterpret_cast<DEV_BROADCAST_HDR*>(lParam)->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
                        service<i_hid_devices>().enumerate_devices();
                    break;
                }
                return TRUE;
            }

            return DefWindowProc(hwnd, message, wParam, lParam);
        }

        static const std::wstring sHidHelperWindowClassName = L"neoGFX::HID_Helper";

        hid_devices::hid_devices() : 
            iHidHelperWindow{ NULL }, iHidHelperNotifyHandle{ NULL }
        {
            WNDCLASSEX wndclass = {};
            wndclass.cbSize = sizeof(wndclass);
            wndclass.hInstance = ::GetModuleHandle(NULL);
            wndclass.lpszClassName = sHidHelperWindowClassName.c_str();
            wndclass.lpfnWndProc = hid_helper_wndproc;
            ::RegisterClassEx(&wndclass);
            iHidHelperWindow = ::CreateWindowEx(0, L"neoGFX::HID_Helper", NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
            DEV_BROADCAST_DEVICEINTERFACE devBroadcast = {};
            devBroadcast.dbcc_size = sizeof(devBroadcast);
            devBroadcast.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
            devBroadcast.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;
            iHidHelperNotifyHandle = ::RegisterDeviceNotification(iHidHelperWindow, &devBroadcast, DEVICE_NOTIFY_WINDOW_HANDLE | DEVICE_NOTIFY_ALL_INTERFACE_CLASSES);
            enumerate_devices();
        }

        hid_devices::~hid_devices()
        {
            ::UnregisterDeviceNotification(iHidHelperNotifyHandle);
            ::DestroyWindow(iHidHelperWindow);
            ::UnregisterClass(sHidHelperWindowClassName.c_str(), ::GetModuleHandle(NULL));
        }

        void hid_devices::enumerate_devices()
        {
            // todo: keyboard and mouse connection/disconnection
            for (auto device = devices().begin(); device != devices().end();)
            {
                switch ((**device).device_class())
                {
                case hid_device_class::Keyboard:
                case hid_device_class::Mouse:
                    ++device;
                    break;
                default:
                    device = remove_device(*device);
                    break;
                }
            }
        }

        hid_device_class hid_devices::device_class(const hid_device_class_uuid& aClassUuid) const
        {
            return hid_device_class::Unknown;
        }

        hid_device_subclass hid_devices::device_subclass(const hid_device_class_uuid& aClassUuid) const
        {
            return hid_device_subclass::Unknown;
        }
    }
}