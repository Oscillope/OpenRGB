/*-----------------------------------------*\
|  MSI3ZoneController.h                     |
|                                           |
|  Definitions and types for MSI/Steelseries|
|  3-Zone Keyboard lighting controller      |
|                                           |
|  Adam Honse (CalcProgrammer1) 12/25/2019  |
\*-----------------------------------------*/

#include "RGBController.h"

#include <string>
#include <hidapi/hidapi.h>

#pragma once

class MSI3ZoneController
{
public:
    MSI3ZoneController(hid_device* dev_handle);
    ~MSI3ZoneController();

    char* GetDeviceName();

    void SetLEDs(std::vector<RGBColor> colors);
    
private:
    char                    device_name[32];
    hid_device*             dev;
};
