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
    std::string AnswerVersionText();
    std::string AnswerHelpText();
    std::string AnswerWrongArgumentUsageText();
    std::string AnswerBadArgumentText(std::string bad_arg);

    std::unique_ptr<nlab::IRelayManager> relay_manager;
};

} // namespace nlab