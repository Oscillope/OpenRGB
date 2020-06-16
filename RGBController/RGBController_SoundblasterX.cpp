#include "RGBController_SoundblasterX.h"

RGBController_SoundblasterX::RGBController_SoundblasterX(SoundblasterXController *sbx_ptr)
{
    sbx = sbx_ptr;

    name = sbx->GetDeviceName();
    type = DEVICE_TYPE_HEADSET;
    description = "SoundblasterX H6 Headset";

    mode Static;
    Static.name       = "Static";
    Static.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Static.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Static);

    mode Off;
    Off.name       = "Off";
    Off.flags      = 0;
    Off.color_mode = MODE_COLORS_NONE;
    modes.push_back(Off);

    SetupZones();
}

void RGBController_SoundblasterX::SetupZones()
{
    zone sbx_zone;
    sbx_zone.name       = "SoundblasterX Zone";
    sbx_zone.type       = ZONE_TYPE_SINGLE;
    sbx_zone.leds_min   = sbx->GetLEDCount();
    sbx_zone.leds_max   = sbx->GetLEDCount();
    sbx_zone.leds_count = sbx->GetLEDCount();
    sbx_zone.matrix_map = NULL;
    zones.push_back(sbx_zone);

    for(std::size_t led_idx = 0; led_idx < zones[0].leds_count; led_idx++) {
        led* new_led = new led();
        new_led->name = "SoundblasterX LED";
        leds.push_back(*new_led);
    }

    SetupColors();
}

void RGBController_SoundblasterX::ResizeZone(int zone, int new_size)
{
    // Nothing to do! The zone size is fixed.
    (void)zone;
    (void)new_size;
}

void RGBController_SoundblasterX::DeviceUpdateLEDs()
{
    sbx->SetLEDColor(&colors[0]);
}

void RGBController_SoundblasterX::UpdateZoneLEDs(int zone)
{
    // There's only one zone
    (void)zone;
    DeviceUpdateLEDs();
}

void RGBController_SoundblasterX::UpdateSingleLED(int led)
{
    // There's only one LED
    (void)led;
    DeviceUpdateLEDs();
}
void RGBController_SoundblasterX::SetCustomMode()
{
    // Custom modes are not supported
}

void RGBController_SoundblasterX::UpdateMode()
{
    if (modes[active_mode].color_mode == MODE_COLORS_NONE) {
        RGBColor off = ToRGBColor(0, 0, 0);
        sbx->SetLEDColor(&off);
    } else {
        sbx->SetLEDColor(&colors[0]);
    }
}
