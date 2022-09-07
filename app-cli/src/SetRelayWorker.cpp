#include "SetRelayWorker.h"

#include "LightArgParser.h"
#include "TextUserInterface.h"
#include "utils.h"

namespace nlab {

SetRelayWorker::SetRelayWorker(std::unique_ptr<nlab::IRelayManager> relay_manager)
    : relay_manager{std::move(relay_manager)}
{
}

bool SetRelayWorker::Run(int argc, char const** argv, std::string& out)
{
    bool ret = true;

    LightArgParser lap(argc, argv);

    Args_t conf_args, data_args;
    std::string bad_arg;

    ret = lap.Parse(conf_args, data_args, bad_arg);

    if (ret)
    {
        ret = false;

        LightArgParserHelper conf_args_h(conf_args);
        LightArgParserHelper data_args_h(data_args);

        if (conf_args.size() == 1 && data_args.size() == 0 &&
            conf_args_h.AnyKeyExists({"h", "help"}))
        {
            out = AnswerHelpText();
            ret = true;
        }
        else if (
            conf_args.size() == 1 && data_args.size() == 0 &&
            conf_args_h.AnyKeyExists({"v", "version"}))
        {
            out = AnswerVersionText();
            ret = true;
        }
        else if (conf_args.size() == 0 && data_args.size() == 1)
        {
        }

        if (!ret) out = AnswerWrongArgumentUsageText();
    }
    else
    {
        out = AnswerBadArgumentText(bad_arg);
    }

    return ret;
}

std::string SetRelayWorker::AnswerVersionText()
{
    return utils::Sprintf(TextUserInterface::kVersion, 0, 0, 1);
}

std::string SetRelayWorker::AnswerHelpText()
{
    return TextUserInterface::kSetRelayHelp;
}

std::string SetRelayWorker::AnswerWrongArgumentUsageText()
{
    return TextUserInterface::kWrongArgumentUsage;
}

std::string SetRelayWorker::AnswerBadArgumentText(std::string bad_arg)
{
    return utils::Sprintf(TextUserInterface::kBadArgument, bad_arg.c_str());
}

} // namespace nlab
