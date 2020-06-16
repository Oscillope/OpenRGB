#include "SoundblasterXController.h"
#include <arpa/inet.h>
#include <cstring>
#include <stdint.h>

SoundblasterXController::SoundblasterXController(hid_device *dev_handle)
{
    handle = dev_handle;

    strcpy(device_name, "SoundblasterX H6");
}

SoundblasterXController::~SoundblasterXController()
{

}

std::string SoundblasterXController::GetDeviceName()
{
    return device_name;
}

#define SBX_H6_CMD_INDEX	1
#define SBX_H6_START_CMD	0x03000100
#define SBX_H6_COLOR_CMD	0x04000000
#define SBX_H6_COLOR_INDEX	4
#define SBX_H6_END_CMD		0x01000000
#define SBX_H6_CMD_LEN		16
void SoundblasterXController::SetLEDColor(RGBColor *color_buf)
{
    unsigned char buf[SBX_H6_CMD_LEN] = { 0 };
    buf[0] = 0xff;	// The first byte is always ff
    // It seems like this string precedes every color write
    *(uint32_t*)(buf + SBX_H6_CMD_INDEX) = htonl(SBX_H6_START_CMD);
    hid_write(handle, buf, SBX_H6_CMD_LEN);
    *(uint32_t*)(buf + SBX_H6_CMD_INDEX) = htonl(SBX_H6_COLOR_CMD);
    // The actual color goes in these 3 bytes
    buf[SBX_H6_COLOR_INDEX] = RGBGetRValue(color_buf[0]);
    buf[SBX_H6_COLOR_INDEX + 1] = RGBGetBValue(color_buf[0]);
    buf[SBX_H6_COLOR_INDEX + 2] = RGBGetGValue(color_buf[0]);
    hid_write(handle, buf, SBX_H6_CMD_LEN);
    // Then we do this to display the color
    *(uint64_t*)(buf + SBX_H6_CMD_INDEX) = htonl(SBX_H6_END_CMD);
    hid_write(handle, buf, SBX_H6_CMD_LEN);
}
