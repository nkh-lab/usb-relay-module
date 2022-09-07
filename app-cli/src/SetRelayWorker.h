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
    std::string AnswerBadArgumentText(const std::string& bad_arg);

    bool AnswerRenameModule(const std::string& module, const std::string& new_module, std::string& out);
    bool AnswerSetChannel(const std::string& module, size_t channel, bool state, std::string& out);

    std::unique_ptr<nlab::IRelayManager> relay_manager;
};

} // namespace nlab