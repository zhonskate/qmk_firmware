#include <print.h>
#include "pointing_device.h"
#include "LUFA/Drivers/Peripheral/ADC.h"

#define STICK_MAX_X 820
#define STICK_MAX_Y 850
#define STICK_MIN_X 190
#define STICK_MIN_Y 202
#define STICK_CENTER_X 532
#define STICK_CENTER_Y 553
#define X_AXIS_DEADZONE 56
#define Y_AXIS_DEADZONE 41

// Map a value from [in_min..in_max] to another value in the range of [out_min..out_max]
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
  return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}

static uint16_t raw_x = 0;
static uint16_t raw_y = 0;
static uint16_t last_x = 0;
static uint16_t last_y = 0;

static int16_t thumbstick_read(uint32_t chanmask, uint16_t high, uint16_t low, uint16_t center, uint8_t deadzone)
{
  uint16_t analogValue = ADC_GetChannelReading(ADC_REFERENCE_AVCC | chanmask);
  if (chanmask == ADC_CHANNEL11)
    raw_x = analogValue;
  else
    raw_y = analogValue;

  // If the current value is too clone to the deadzone, do not move the mouse.
//   if (abs((int)analogValue - center) <= deadzone)
//     return 0;

  // Map the analog read value from 0 to 1024 to between -127 and 127 so that it can be fed to
  // mouseReport.
  // But in reality we never reach 0 and 1024 because the joystick is not that precise, so just
  // map from the empiric range. (Note that these values as specific to your thumbstick, if you want finer control
  // you need to adjust the defines to fit your readings).
  int32_t vMapped = map(
      (int)analogValue,
      low,
      high,
      -127,
      127);

  return vMapped * 1/8;
}

static int32_t thumbstick_read_x(void)
{
  return thumbstick_read(ADC_CHANNEL11, STICK_MAX_X, STICK_MIN_X, STICK_CENTER_X, X_AXIS_DEADZONE);
}

static int32_t thumbstick_read_y(void)
{
  return thumbstick_read(ADC_CHANNEL12, STICK_MAX_Y, STICK_MIN_Y, STICK_CENTER_Y, Y_AXIS_DEADZONE);
}

void init_thumbstick(void) {
    // Turn on the ADC for reading the thumbstick
    ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_32);
    ADC_SetupChannel(11); // Y
    ADC_SetupChannel(12); // X
}

void process_thumbstick(void)
{
//   int8_t x = thumbstick_read_x();
//   int8_t y = thumbstick_read_y();
  thumbstick_read_x();
  thumbstick_read_y();
  if ((last_x != raw_x) || (last_y != raw_y)) {
      last_x = raw_x;
      last_y = raw_y;
      uprintf("X: %u; Y: %u\n", raw_x, raw_y);
  }

//   if (x || y) {
    //   report_mouse_t currentReport = pointing_device_get_report();
    //   currentReport.x = -x; // mounted left-side right
    //   currentReport.y = y;
    //   currentReport.v = 0;
    //   currentReport.h = 0;
    //   pointing_device_set_report(currentReport);
//   }
}
