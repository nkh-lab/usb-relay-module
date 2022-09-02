#include "GetRelayWorker.h"

#include "LightArgParser.h"
#include "TextUserInterface.h"
#include "utils.h"

namespace {
const char* kAllRelays = "";
const size_t kAllChannels = 0;
const char* kRelayChannelDelimiter = "_";
} // namespace

namespace nlab {

GetRelayWorker::GetRelayWorker(std::unique_ptr<nlab::IRelayManager> relay_manager)
    : relay_manager{std::move(relay_manager)}
{
}

bool GetRelayWorker::CheckArgsAndAnswer(int argc, char const** argv, std::string& out)
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
        else if (conf_args.size() == 0)
        {
            std::string req_relay{kAllRelays};
            size_t req_channel{kAllChannels};

            if (data_args.size() == 0)
            {
                ret = true;
            }
            else if (data_args.size() == 1)
            {
                std::string s = data_args.begin()->first;
                req_relay = s;
                size_t delimiter_pos = s.find_first_of(kRelayChannelDelimiter);

                if (delimiter_pos != std::string::npos)
                {
                    req_relay = s.substr(0, delimiter_pos);
                    req_channel = std::stoi(s.substr(delimiter_pos + 1));
                }
                ret = true;
            }

            if (ret) out = AnswerRelayStateText(req_relay, req_channel);
        }

        if (!ret) out = AnswerWrongArgumentUsageText();
    }
    else
    {
        out = AnswerBadArgumentText(bad_arg);
    }

    return ret;
}

std::string GetRelayWorker::AnswerVersionText()
{
    return utils::Sprintf(TextUserInterface::kVersion, 0, 0, 1);
}

std::string GetRelayWorker::AnswerHelpText()
{
    return TextUserInterface::kHelp;
}

std::string GetRelayWorker::AnswerWrongArgumentUsageText()
{
    return "This is wrong argument usage text!\n";
}

std::string GetRelayWorker::AnswerBadArgumentText(std::string bad_arg)
{
    return utils::Sprintf(TextUserInterface::kBadArgument, bad_arg.c_str());
}

std::string GetRelayWorker::AnswerRelayStateText(std::string relay, size_t channel)
{
    std::string ret{"No USB relay module detected\n"};

    auto modules = relay_manager->GetModules();

    for (auto m : modules)
    {
    }

    return ret;
}

} // namespace nlab
