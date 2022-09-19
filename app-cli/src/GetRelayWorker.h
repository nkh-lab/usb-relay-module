#pragma once

#include <string>
#include <vector>

#include "RelayManager.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appcli {

class GetRelayWorker
{
public:
    GetRelayWorker(std::unique_ptr<IRelayManager> relay_manager);
    ~GetRelayWorker() = default;

    bool Run(int argc, char const** argv, std::string& out);

private:
    std::string DoVersionText();
    std::string DoHelpText();
    std::string DoWrongArgumentUsageText();
    std::string DoBadArgumentText(const std::string& bad_arg);

    bool GetState(const std::string& relay, size_t channel, std::string& out);
    bool GetStatesAllModules(const IRelayModulePtrs& modules, std::string& out);
    bool GetStatesRequestedModule(
        const IRelayModulePtrs& modules,
        const std::string& module,
        std::string& out);
    bool GetStateRequestedChannel(
        const IRelayModulePtrs& modules,
        const std::string& module,
        size_t channel,
        std::string& out);

    std::unique_ptr<IRelayManager> relay_manager_;
};

} // namespace appcli
} // namespace usbrelaymodule
} // namespace nkhlab