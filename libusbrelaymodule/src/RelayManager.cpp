/*
 * Copyright (C) 2022 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#include "RelayManager.h"
#include "RelayManagerHidapi.h"
#include "RelayModuleDcttech.h"
#ifdef URM_SIMU
#include "simu/RelayManagerSimu.h"
#include "simu/RelayModuleSimu.h"
#endif

namespace nkhlab {
namespace usbrelaymodule {

IRelayManagerPtr CreateHidapiManagerForDcttechModules()
{
    return std::make_unique<impl::RelayManagerHidapi<impl::RelayModuleDcttech>>();
}

#ifdef URM_SIMU
IRelayManagerPtr CreateSimuManager()
{
    return std::make_unique<impl::RelayManagerSimu<impl::RelayModuleSimu>>();
}
#endif

} // namespace usbrelaymodule
} // namespace nkhlab