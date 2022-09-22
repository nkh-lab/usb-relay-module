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

#pragma once

#include <string>

#define UNUSED(x) static_cast<void>(x)

namespace nkhlab {
namespace usbrelaymodule {
namespace utils {

std::string PrintBytes(uint8_t* bytes, size_t size);
std::string GetStrFromBytes(uint8_t* bytes, size_t size);
std::string PwstrToStr(wchar_t* pwstr);
std::string Sprintf(const char* fmt, ...);
void SplitModuleChannelStr(const std::string& module_channel, std::string& module, size_t& channel);

} // namespace utils
} // namespace usbrelaymodule
} // namespace nkhlab