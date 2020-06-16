/*-----------------------------------------*\
|  SoundblasterXController.h                |
|                                           |
|  Definitions and types for SoundblasterX  |
|  headsets and DACs                        |
|                                           |
|  oscillope                  15/06/2020    |
\*-----------------------------------------*/

#pragma once

#include "RGBController.h"
#include <hidapi/hidapi.h>

class SoundblasterXController
{
public:
    SoundblasterXController(hid_device* dev_handle);
    ~SoundblasterXController();

    std::string     GetDeviceName();
    unsigned int    GetLEDCount() { return 1; }

    void            SetLEDColor(RGBColor* color_buf);

private:
    hid_device*             handle;
    char                    device_name[32];
};
