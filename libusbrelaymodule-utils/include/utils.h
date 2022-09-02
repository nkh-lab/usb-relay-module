#pragma once

#include <string>

#define NOT_USED(x) static_cast<void>(x)

namespace nlab {
namespace utils {

std::string BytesToStr(uint8_t* bytes, size_t size);
std::string PwstrToStr(wchar_t* pwstr);
std::string Sprintf(const char* fmt, ...);

} // namespace utils
} // namespace nlab