#pragma once

#include <iostream>

#include "IRelayManager.h"
#include "RelayModuleDcttech.h"

namespace nlab {

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

        return l;
    }
};

} // namespace nlab