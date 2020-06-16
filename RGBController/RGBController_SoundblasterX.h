#pragma once

#include "RGBController.h"
#include "SoundblasterXController.h"

class RGBController_SoundblasterX : public RGBController
{
public:
    RGBController_SoundblasterX(SoundblasterXController *sbx_ptr);

    void SetupZones();
    void ResizeZone(int zone, int new_size);

    void DeviceUpdateLEDs();
    void UpdateZoneLEDs(int zone);
    void UpdateSingleLED(int led);

    void UpdateMode();
    void SetCustomMode();

private:
    SoundblasterXController *sbx;
};
