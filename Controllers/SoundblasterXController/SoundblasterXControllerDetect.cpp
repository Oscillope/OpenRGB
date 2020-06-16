#include "SoundblasterXController.h"
#include "RGBController.h"
#include "RGBController_SoundblasterX.h"
#include <hidapi/hidapi.h>
#include <vector>

#define SoundblasterX_H6_VID 0x041e
#define SoundblasterX_H6_PID 0x3255

void DetectSoundblasterXControllers(std::vector<RGBController*> &rgb_controllers)
{
    hid_device *dev = NULL;

    hid_init();

    dev = hid_open(SoundblasterX_H6_VID, SoundblasterX_H6_PID, NULL);

    if (dev) {
        SoundblasterXController *controller = new SoundblasterXController(dev);
        RGBController_SoundblasterX *rgb_controller = new RGBController_SoundblasterX(controller);
        rgb_controller->name = "SoundblasterX H6";
        rgb_controllers.push_back(rgb_controller);
    }
}
