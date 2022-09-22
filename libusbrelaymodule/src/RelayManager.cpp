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

namespace nkhlab {
namespace usbrelaymodule {

std::unique_ptr<IRelayManager> CreateHidapiManagerForDcttechModules()
{
    return std::make_unique<impl::RelayManagerHidapi<impl::RelayModuleDcttech>>();
}

} // namespace usbrelaymodule
} // namespace nkhlab