/*
 * Copyright (C) 2022 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#include <RelayModuleDcttech.h>

#include <bitset>
#include <cstring>

#include "hidapi.h"

#include "Utils.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

RelayModuleDcttech::RelayModuleDcttech(const std::string& info, const std::string& path, size_t channels_size)
    : info_{info}
    , path_{path}
    , channels_size_{channels_size}
{
}

uint16_t RelayModuleDcttech::GetVendorId()
{
    return kUsbVendorId;
}

uint16_t RelayModuleDcttech::GetProductId()
{
    return kUsbProductId;
}

std::string RelayModuleDcttech::GetInfo()
{
    return info_;
}

bool RelayModuleDcttech::GetNameAndChannels(std::string& module_name, std::vector<bool>& channels)
{
    bool ret = false;

    hid_device* handle = hid_open_path(path_.c_str());

    if (handle)
    {
        uint8_t data[kDataSizeBytes] = {0};
        data[0] = kReportIDGet;

        int hid_ret = hid_get_feature_report(handle, data, sizeof(data));

        if (hid_ret != -1)
        {
#ifdef __linux__
            module_name = utils::GetStrFromBytes(&data[0], kNameSizeBytes);
            uint8_t& relays_state = data[7];
#else
            module_name = utils::GetStrFromBytes(&data[1], kNameSizeBytes);
            uint8_t& relays_state = data[8];
#endif
            auto channels_states = std::bitset<8>(relays_state);

            for (size_t i = 0; i < channels_size_ && i < 8; ++i)
            {
                channels.emplace_back(channels_states[i]);
            }

            ret = true;
        }

        hid_close(handle);
    }

    return ret;
}

bool RelayModuleDcttech::SetName(const std::string& name)
{
    bool ret = false;

    hid_device* handle = hid_open_path(path_.c_str());

    if (handle)
    {
        size_t name_size_to_copy = name.size() < kNameSizeBytes ? name.size() : kNameSizeBytes;

        uint8_t data[kDataSizeBytes] = {0};
        data[0] = kReportIDSet;
        data[1] = kCmdSetModuleName;
        std::copy(name.cbegin(), name.cbegin() + name_size_to_copy, &data[2]);

        int hid_ret = hid_send_feature_report(handle, data, sizeof(data));

        if (hid_ret != -1) ret = true;

        hid_close(handle);
    }

    return ret;
}

bool RelayModuleDcttech::SetChannel(size_t channel, bool state)
{
    bool ret = false;

    hid_device* handle = hid_open_path(path_.c_str());

    if (handle)
    {
        uint8_t data[kDataSizeBytes] = {0};
        data[0] = kReportIDSet;
        data[1] = state ? kCmdRelayOn : kCmdRelayOff;
        data[2] = static_cast<uint8_t>(channel);

        int hid_ret = hid_send_feature_report(handle, data, sizeof(data));

        if (hid_ret != -1) ret = true;

        hid_close(handle);
    }

    return ret;
}

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab