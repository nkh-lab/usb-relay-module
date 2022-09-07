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

bool GetRelayWorker::Run(int argc, char const** argv, std::string& out)
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
                utils::SplitModuleChannelStr(data_args.begin()->first, req_relay, req_channel);
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
    return TextUserInterface::kGetRelayHelp;
}

std::string GetRelayWorker::AnswerWrongArgumentUsageText()
{
    return TextUserInterface::kWrongArgumentUsage;
}

std::string GetRelayWorker::AnswerBadArgumentText(const std::string& bad_arg)
{
    return utils::Sprintf(TextUserInterface::kBadArgument, bad_arg.c_str());
}

std::string GetRelayWorker::AnswerRelayStateText(const std::string& relay, size_t channel)
{
    auto modules = relay_manager->GetModules();

    if (!modules.size()) return TextUserInterface::kNoModules;

    if (relay.empty())
        return AnswerRelayStateText4AllModules(modules);
    else
    {
        if (channel == 0)
            return AnswerRelayStateText4Module(modules, relay);
        else
            return AnswerRelayStateText4ModuleAndChannel(modules, relay, channel);
    }
}

std::string GetRelayWorker::AnswerRelayStateText4AllModules(const IRelayModulePtrs& modules)
{
    std::string ret;

    for (auto m : modules)
    {
        std::string module_name, channels_out;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        for (size_t i = 0; i < channels.size(); ++i)
        {
            channels_out += utils::Sprintf(
                TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(channels[i]));
        }

        ret += utils::Sprintf(
            TextUserInterface::kGetRelayInfoAndState,
            m->GetInfo().c_str(),
            module_name.c_str(),
            channels_out.c_str());
    }

    return ret;
}

std::string GetRelayWorker::AnswerRelayStateText4Module(
    const IRelayModulePtrs& modules,
    const std::string& module)
{
    std::string ret = utils::Sprintf(TextUserInterface::kNoRequestedModule, module.c_str());

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == module)
        {
            std::string channels_out;

            for (size_t i = 0; i < channels.size(); ++i)
            {
                channels_out += utils::Sprintf(
                    TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(channels[i]));
            }

            ret = utils::Sprintf(
                TextUserInterface::kGetRelayInfoAndState,
                m->GetInfo().c_str(),
                module_name.c_str(),
                channels_out.c_str());
        }
    }

    return ret;
}

std::string GetRelayWorker::AnswerRelayStateText4ModuleAndChannel(
    const IRelayModulePtrs& modules,
    const std::string& module,
    size_t channel)
{
    std::string ret{TextUserInterface::kNoRequestedModule};

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == module)
        {
            if (channel <= channels.size())
            {
                ret = utils::Sprintf(
                    TextUserInterface::kGetChannelState, static_cast<int>(channels[channel - 1]));
            }
            else
            {
                ret = utils::Sprintf(TextUserInterface::kNoRequestedChannel, channel, module.c_str());
            }
        }
    }

    return ret;
}

} // namespace nlab
