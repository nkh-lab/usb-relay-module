#pragma once

#include <IRelayModule.h>

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

class RelayModuleDcttech final : public IRelayModule
{
public:
    RelayModuleDcttech(const std::string& info, const std::string& path, size_t channels_size);
    ~RelayModuleDcttech() = default;

    static uint16_t GetVendorId();
    static uint16_t GetProductId();

    std::string GetInfo() override;
    bool GetNameAndChannels(std::string& module_name, std::vector<bool>& channels) override;
    bool SetName(const std::string& name) override;
    bool SetChannel(size_t channel, bool state) override;

private:
    static const uint16_t kUsbVendorId = 0x16c0;
    static const uint16_t kUsbProductId = 0x05df;

    static const size_t kDataSizeBytes = 9;
    static const size_t kNameSizeBytes = 5;

    static const uint8_t kReportIDGet = 0x01;
    static const uint8_t kReportIDSet = 0x00;

    static const uint8_t kCmdRelayOn = 0xff;
    static const uint8_t kCmdRelayOff = 0xfd;
    static const uint8_t kCmdSetModuleName = 0xfa;

    const std::string info_;
    const std::string path_;
    const size_t channels_size_;
};

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab