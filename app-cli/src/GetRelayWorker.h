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

    bool Run(int argc, char const** argv, std::string& out);

private:
    std::string AnswerVersionText();
    std::string AnswerHelpText();
    std::string AnswerWrongArgumentUsageText();
    std::string AnswerBadArgumentText(const std::string& bad_arg);
    std::string AnswerRelayStateText(const std::string& relay, size_t channel);
    std::string AnswerRelayStateText4AllModules(const IRelayModulePtrs& modules);
    std::string AnswerRelayStateText4Module(const IRelayModulePtrs& modules, const std::string& module);
    std::string AnswerRelayStateText4ModuleAndChannel(
        const IRelayModulePtrs& modules,
        const std::string& module,
        size_t channel);

    std::unique_ptr<nlab::IRelayManager> relay_manager;
};

} // namespace nlab