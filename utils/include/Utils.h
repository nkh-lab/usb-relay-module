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