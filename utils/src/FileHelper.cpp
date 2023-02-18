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

#include "FileHelper.h"

#include <fstream>

namespace nkhlab {
namespace usbrelaymodule {
namespace utils {

bool FileHelper::ExistFile(const std::string& file)
{
    bool ret = false;
    std::ifstream ifs(file);

    if (ifs.good()) ret = true;

    return ret;
}

std::stringstream FileHelper::ReadFile(const std::string& file)
{
    std::ifstream ifs(file);
    std::stringstream ss;

    ss << ifs.rdbuf();

    return ss;
}

void FileHelper::WriteFile(const std::string& file, const std::string& data)
{
    std::ofstream ofs(file);

    ofs << data;
}

} // namespace utils
} // namespace usbrelaymodule
} // namespace nkhlab