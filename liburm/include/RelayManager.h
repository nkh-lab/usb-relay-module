#pragma once

#include <list>
#include <memory>

#include "IRelayManager.h"

namespace urm {

std::unique_ptr<IRelayManager> CreateHidapiManagerForDcttechModules();

}