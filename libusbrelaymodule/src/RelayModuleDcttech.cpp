#include <RelayModuleDcttech.h>

#include "utils.h"

namespace nlab {

RelayModuleDcttech::RelayModuleDcttech(const std::string& path)
    : path{path}
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
    return "";
}

bool RelayModuleDcttech::GetNameAndChannels(std::string& module_name, std::vector<bool>& channels)
{
    UNUSED(module_name);
    UNUSED(channels);

    return false;
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