#pragma once

#include <string>
#include <vector>

#include "RelayManager.h"

namespace nlab {

class GetRelayWorker
{
public:
    GetRelayWorker(std::unique_ptr<nlab::IRelayManager> relay_manager);
    ~GetRelayWorker() = default;

    bool CheckArgsAndAnswer(int argc, char const** argv, std::string& out);

private:
    std::string AnswerVersionText();
    std::string AnswerHelpText();
    std::string AnswerWrongArgumentUsageText();
    std::string AnswerBadArgumentText(std::string bad_arg);
    std::string AnswerRelayStateText(std::string relay, size_t channel);

    std::unique_ptr<nlab::IRelayManager> relay_manager;
};

} // namespace nlab