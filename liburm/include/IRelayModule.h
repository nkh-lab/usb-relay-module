#pragma once

#include <string>
#include <vector>

namespace urm {

class IRelayModule
{
public:
    virtual ~IRelayModule() = default;

    virtual std::string GetPath() = 0;

    virtual bool GetNameAndChannels(std::string& module_name, std::vector<bool>& channels) = 0;
    virtual bool SetName(const std::string& name) = 0;
    virtual bool SetChannel(size_t channel, bool state) = 0;
};

} // namespace urm