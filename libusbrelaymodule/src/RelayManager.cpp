#include "RelayManager.h"
#include "RelayManagerHidapi.h"
#include "RelayModuleDcttech.h"

namespace nkhlab {
namespace usbrelaymodule {

std::unique_ptr<IRelayManager> CreateHidapiManagerForDcttechModules()
{
    return std::make_unique<impl::RelayManagerHidapi<impl::RelayModuleDcttech>>();
}

} // namespace usbrelaymodule
} // namespace nkhlab