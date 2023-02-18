/*
 * Copyright (C) 2023 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#pragma once

#include <sstream>
#include <string>

namespace nkhlab {
namespace usbrelaymodule {
namespace utils {

class FileHelper
{
public:
    FileHelper() = delete;

    static bool ExistFile(const std::string& file);

    static std::stringstream ReadFile(const std::string& file);
    static void WriteFile(const std::string& file, const std::string& data);
};

} // namespace utils
} // namespace usbrelaymodule
} // namespace nkhlab