#include "M5UnifiedW.h"

void setup(void)
{
    M5.begin();
}

void loop()
{
    static uint8_t color = 0;
    delay(2000);

    static constexpr uint16_t colors[] = {
        TFT_WHITE, TFT_CYAN, TFT_RED, TFT_YELLOW, TFT_BLUE, TFT_GREEN};

    M5.Display.startWrite();
    M5.Display.fillScreen(colors[color]);
    Serial.printf("color: %04x\r\n", colors[color]);
    color = (color + 1) % (sizeof(colors) / sizeof(colors[0]));

    M5.Display.setCursor(0, 0);
    M5.Display.setFont(&fonts::Font0);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Display.setTextSize(1);
    M5.Display.print("print");

    M5.Display.endWrite();
}
