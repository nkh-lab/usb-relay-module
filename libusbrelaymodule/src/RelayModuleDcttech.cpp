#include <RelayModuleDcttech.h>

#include <bitset>

#include "hidapi.h"

#include "utils.h"

namespace nlab {

RelayModuleDcttech::RelayModuleDcttech(const std::string& info, const std::string& path, size_t channels_size)
    : info{info}
    , path{path}
    , channels_size{channels_size}
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
    return info;
}

bool RelayModuleDcttech::GetNameAndChannels(std::string& module_name, std::vector<bool>& channels)
{
    bool ret = false;

    hid_device* handle = hid_open_path(path.c_str());

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

            for (size_t i = 0; i < channels_size && i < 8; ++i)
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
    UNUSED(name);

    return false;
}

bool RelayModuleDcttech::SetChannel(size_t channel, bool state)
{
    UNUSED(channel);
    UNUSED(state);

    return false;
}

} // namespace nlab