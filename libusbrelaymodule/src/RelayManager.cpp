#include "RelayManager.h"
#include "RelayManagerHidapi.h"
#include "RelayModuleDcttech.h"

namespace nlab {

std::unique_ptr<IRelayManager> CreateHidapiManagerForDcttechModules()
{
    return std::make_unique<RelayManagerHidapi<RelayModuleDcttech>>();
}

} // namespace nlab