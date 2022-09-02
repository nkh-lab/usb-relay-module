#include <RelayModuleDcttech.h>

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

std::string RelayModuleDcttech::GetPath()
{
    return path;
}

bool RelayModuleDcttech::GetNameAndChannels(std::string& module_name, std::vector<bool>& channels)
{
    return false;
}

bool RelayModuleDcttech::SetName(const std::string& name)
{
    return false;
}

bool RelayModuleDcttech::SetChannel(size_t channel, bool state)
{
    return false;
}

} // namespace nlab