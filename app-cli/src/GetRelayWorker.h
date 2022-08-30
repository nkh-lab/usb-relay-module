#pragma once

#include <sstream>
#include <vector>

#include "RelayManager.h"

namespace nlab {

class GetRelayWorker
{
public:
    GetRelayWorker(std::unique_ptr<urm::IRelayManager> relay_manager);
    ~GetRelayWorker() = default;

    bool Do(int argc, char const** argv, std::stringstream& out);

private:
    std::string DoVersionText();
    std::string DoHelpText();
    std::string DoWrongArgumentUsageText();
    std::string DoBadArgumentText(std::string bad_arg);
    std::string DoRelayStateText(std::string relay, size_t channel);

    std::unique_ptr<urm::IRelayManager> relay_manager;
};

} // namespace nlab