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
    out.clear();

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
            out = DoHelpText();
            ret = true;
        }
        else if (
            conf_args.size() == 1 && data_args.size() == 0 &&
            conf_args_h.AnyKeyExists({"v", "version"}))
        {
            out = DoVersionText();
            ret = true;
        }
        else if (conf_args.size() == 0 && data_args.size() == 1)
        {
            std::string req_module{};
            size_t req_channel = 0;

            utils::SplitModuleChannelStr(data_args.begin()->first, req_module, req_channel);

            if (req_channel == 0 && !data_args.begin()->second.empty() &&
                data_args.begin()->second[0] != '1' && data_args.begin()->second[0] != '0')
            {
                std::string new_name{data_args.begin()->second};
                ret = RenameModule(req_module, data_args.begin()->second, out);
            }
            else if (req_channel > 0 && (data_args.begin()->second[0] == '1' || data_args.begin()->second[0] == '0'))
            {
                bool state = data_args.begin()->second[0] == '1' ? true : false;
                ret = SetChannel(req_module, req_channel, state, out);
            }
        }

        if (!ret && out.empty()) out = DoWrongArgumentUsageText();
    }
    else
    {
        out = DoBadArgumentText(bad_arg);
    }

    return ret;
}

std::string SetRelayWorker::DoVersionText()
{
    return utils::Sprintf(TextUserInterface::kVersion, 0, 0, 1);
}

std::string SetRelayWorker::DoHelpText()
{
    return TextUserInterface::kSetRelayHelp;
}

std::string SetRelayWorker::DoWrongArgumentUsageText()
{
    return TextUserInterface::kErrorWrongArgumentUsage;
}

std::string SetRelayWorker::DoBadArgumentText(const std::string& bad_arg)
{
    return utils::Sprintf(TextUserInterface::kErrorBadArgument, bad_arg.c_str());
}

bool SetRelayWorker::RenameModule(const std::string& module, const std::string& new_module, std::string& out)
{
    bool ret = false;

    out = utils::Sprintf(TextUserInterface::kErrorNoRequestedModule, module.c_str());

    auto modules = relay_manager->GetModules();

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == module)
        {
            ret = m->SetName(new_module);
            out.clear();
        }
    }

    return ret;
}

bool SetRelayWorker::SetChannel(const std::string& module, size_t channel, bool state, std::string& out)
{
    bool ret = false;

    out = utils::Sprintf(TextUserInterface::kErrorNoRequestedModule, module.c_str());

    auto modules = relay_manager->GetModules();

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == module)
        {
            if (channel <= channels.size())
            {
                ret = m->SetChannel(channel, state);
                out.clear();
            }
            else
            {
                ret = false;
                out = utils::Sprintf(
                    TextUserInterface::kErrorNoRequestedChannel, channel, module.c_str());
            }
        }
    }

    return ret;
}

} // namespace nlab
