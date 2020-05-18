typedef enum CommandCode {
  SOFTWARE_RESET = 0x01u,
  SLEEP_OUT = 0x11u,
  GAMMA_SET = 0x26u,
  DISPLAY_ON = 0x29u,
  COLUMN_ADDRESS_SET = 0x2Au,
  PAGE_ADDRESS_SET = 0x2Bu,
  MEMORY_WRITE = 0x2Cu,
  MEMORY_ACCESS_CONTROL = 0x36u,
  PIXEL_FORMAT_SET = 0x3Au,
  FRAME_RATE_CONTROL = 0xB1u,
  DISPLAY_FUNCTION_CONTROL = 0xB6u,
  POWER_CONTROL_1 = 0xC0u,
  POWER_CONTROL_2 = 0xC1u,
  VCOM_CONTROL_1= 0xC5u,
  VCOM_CONTROL_2 = 0xC7u,
  POWER_CONTROL_A = 0xCBu,
  POWER_CONTROL_B = 0xCFu,
  POSITIVE_GAMMA_CORRECTION = 0xE0u,
  NEGATIVE_GAMMA_CORRECTION = 0xE1u,
  DRIVER_TIMING_CONTROL_A = 0xE8u,
  DRIVER_TIMING_CONTROL_B = 0xEAu,
  POWER_ON_SEQUENCE_CONTROL = 0xEDu,
  UNDOCUMENTED_1 = 0xEFu,
  ENABLE_3G = 0xF2u,
  INTERFACE_CONTROL = 0xF6u,
  PUMP_RATIO_CONTROL = 0xF7u
} command_code_e;

typedef struct Command {
  command_code_e code;
  uint8_t length;
  uint8_t parameters[15];
} command_t;

static const command_t initializationCommands[] = {
  {
    SOFTWARE_RESET,
    0,
    {}
  },
  {
    UNDOCUMENTED_1,
    3,
    {0x03, 0x80, 0x02}
  },
  {
    POWER_CONTROL_B,
    3,
    {0x00, 0xC1, 0x30}
  },
  {
    POWER_ON_SEQUENCE_CONTROL,
    4,
    {0x64, 0x03, 0x12, 0x81}
  },
  {
    DRIVER_TIMING_CONTROL_A,
    3,
    {0x85, 0x00, 0x78}
  },
  {
    POWER_CONTROL_A,
    5,
    {0x39, 0x2C, 0x00, 0x34, 0x02}
  },
  {
    PUMP_RATIO_CONTROL,
    1,
    {0x20}
  },
  {
    DRIVER_TIMING_CONTROL_B,
    2,
    {0x00, 0x00}
  },
  {
    POWER_CONTROL_1,
    1,
    {0x23}
  },
  {
    POWER_CONTROL_2,
    1,
    {0x10}
  },
  {
    VCOM_CONTROL_1,
    2,
    {0x3E, 0x28}
  },
  {
    VCOM_CONTROL_2,
    1,
    {0x86}
  },
  {
    MEMORY_ACCESS_CONTROL,
    1,
    {0x48}
  },
  {
    PIXEL_FORMAT_SET,
    1,
    {0x55}
  },
  {
    FRAME_RATE_CONTROL,
    2,
    {0x00, 0x18}
  },
  {
    DISPLAY_FUNCTION_CONTROL,
    3,
    {0x08, 0x82, 0x27}
  },
  {
    ENABLE_3G,
    1,
    {0x00}
  },
  {
    GAMMA_SET,
    1,
    {0x01}
  },
  {
    POSITIVE_GAMMA_CORRECTION,
    15,
    {0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00}
  },
  {
    NEGATIVE_GAMMA_CORRECTION,
    15,
    {0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F}
  },
  {
    SLEEP_OUT,
    0,
    {}
  },
  {
    DISPLAY_ON,
    0,
    {}
  },
};
