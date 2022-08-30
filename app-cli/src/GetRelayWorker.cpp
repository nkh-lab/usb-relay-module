#include "GetRelayWorker.h"

#include "LightArgParser.h"

namespace {
const char* kAllRelays = "";
const size_t kAllChannels = 0;
const char* kRelayChannelDelimiter = "_";
} // namespace

namespace nlab {

GetRelayWorker::GetRelayWorker(std::unique_ptr<urm::IRelayManager> relay_manager)
    : relay_manager{std::move(relay_manager)}
{
}

bool GetRelayWorker::Do(int argc, char const** argv, std::stringstream& out)
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
            out << DoHelpText();
            ret = true;
        }
        else if (
            conf_args.size() == 1 && data_args.size() == 0 &&
            conf_args_h.AnyKeyExists({"v", "version"}))
        {
            out << DoVersionText();
            ret = true;
        }
        else
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

            if (ret) out << DoRelayStateText(req_relay, req_channel);
        }

        if (!ret) out << DoWrongArgumentUsageText();
    }
    else
    {
        out << DoBadArgumentText(bad_arg);
    }

    return ret;
}

std::string GetRelayWorker::DoVersionText()
{
    return "v1.0.0\n";
}

std::string GetRelayWorker::DoHelpText()
{
    return "This is help text!\n";
}

std::string GetRelayWorker::DoWrongArgumentUsageText()
{
    return "This is wrong argument usage text!\n";
}

std::string GetRelayWorker::DoBadArgumentText(std::string bad_arg)
{
    std::stringstream ss;
    ss << "This is bad argument: " << bad_arg << " text!\n";
    return ss.str();
}

std::string GetRelayWorker::DoRelayStateText(std::string relay, size_t channel)
{
    std::stringstream ss;

    auto modules = relay_manager->GetModules();

    if (modules.size() == 0)
    {
        ss << "No USB relay module detected\n";
    }
    else
    {
        for (auto m : modules)
        {
        }
    }

    return ss.str();
}

} // namespace nlab
