#pragma once

#include <string>
#include <vector>

#ifdef __linux__
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

namespace nkhlab {
namespace usbrelaymodule {

class DLL_EXPORT IRelayModule
{
public:
    virtual ~IRelayModule() = default;

    virtual std::string GetInfo() = 0;

    virtual bool GetNameAndChannels(std::string& module_name, std::vector<bool>& channels) = 0;

    virtual bool SetName(const std::string& name) = 0;
    virtual bool SetChannel(size_t channel, bool state) = 0;
};

} // namespace usbrelaymodule
} // namespace nkhlab

#undef DLL_EXPORT