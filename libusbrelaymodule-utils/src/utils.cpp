#include "utils.h"

#include <iomanip>
#include <sstream>

namespace urm {
namespace utils {

std::string BytesToStr(uint8_t* bytes, size_t size)
{
    std::stringstream ss;

    ss << std::hex;
    for (int i = 0; i < size; ++i)
    {
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(bytes[i]);
        if (i < size - 1) ss << " ";
    }

    return ss.str();
}

std::string PwstrToStr(wchar_t* pwstr)
{
    std::string str = "(null)";
    if (pwstr)
    {
        std::wstring wstr = std::wstring(pwstr);
        str = std::string(wstr.begin(), wstr.end());
    }

    return str;
}

} // namespace utils
} // namespace urm