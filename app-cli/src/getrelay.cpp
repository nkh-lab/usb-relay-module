#include <iostream>

#include "RelayManager.h"
#include "utils.h"

int main(int argc, char const* argv[])
{
    NOT_USED(argc);

    std::cout << "Hello World from " << argv[0] << "\n";

    auto RelayManager = urm::CreateHidapiManagerForDcttechModules();

    auto modules = RelayManager->GetModules();

    for (auto m : modules) std::cout << m->GetPath() << "\n";

    return EXIT_SUCCESS;
}