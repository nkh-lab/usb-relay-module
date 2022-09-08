#pragma once

#include <string>
#include <vector>

#include "RelayManager.h"

namespace nlab {

class SetRelayWorker
{
public:
    SetRelayWorker(std::unique_ptr<nlab::IRelayManager> relay_manager);
    ~SetRelayWorker() = default;

    bool Run(int argc, char const** argv, std::string& out);

private:
    std::string DoVersionText();
    std::string DoHelpText();
    std::string DoWrongArgumentUsageText();
    std::string DoBadArgumentText(const std::string& bad_arg);

    bool RenameModule(const std::string& module, const std::string& new_module, std::string& out);
    bool SetChannel(const std::string& module, size_t channel, bool state, std::string& out);

    std::unique_ptr<nlab::IRelayManager> relay_manager_;
};

} // namespace nlab