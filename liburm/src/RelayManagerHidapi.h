#pragma once

#include <iostream>

#include "IRelayManager.h"
#include "RelayModuleDcttech.h"

namespace urm {

using IRelayModulePtr = std::shared_ptr<IRelayModule>;

template <typename TRelayModule>
class RelayManagerHidapi final : public IRelayManager
{
public:
    RelayManagerHidapi() = default;
    ~RelayManagerHidapi() = default;

    std::list<IRelayModulePtr> GetModules() override
    {
        std::list<IRelayModulePtr> l;

        l.push_back(std::make_shared<RelayModuleDcttech>("/dev/path1"));
        l.push_back(std::make_shared<RelayModuleDcttech>("/dev/path2"));

        return l;
    }
};

} // namespace urm