#include <M5UnifiedW.h>

// This sketch mirrors the upstream M5Unified "Button" example but runs on
// the M5Wokwi shim. Display output is stubbed for now, while button queries
// always report "not pressed". Use it to verify that the library builds.

void setup()
{
    M5.begin();

    M5.Display.setEpdMode(m5wokwi::epd_mode_t::epd_fastest);

    if (M5.Display.width() < M5.Display.height())
    {
        // Landscape orientation to match typical M5Stack units.
        M5.Display.setRotation(M5.Display.getRotation() ^ 1);
    }
}

void loop()
{
    M5.delay(1);
    M5.update();

    static constexpr uint16_t colors[] = {
        TFT_WHITE, TFT_CYAN, TFT_RED, TFT_YELLOW, TFT_BLUE, TFT_GREEN};

    static constexpr const char *names[] = {
        "none", "wasHold", "wasClicked", "wasPressed", "wasReleased", "wasDecideCount"};

    const int w = M5.Display.width() / 5;
    const int h = M5.Display.height();

    M5.Display.startWrite();

    const int statePWR = M5.BtnPWR.wasHold()               ? 1
                         : M5.BtnPWR.wasClicked()          ? 2
                         : M5.BtnPWR.wasPressed()          ? 3
                         : M5.BtnPWR.wasReleased()         ? 4
                         : M5.BtnPWR.wasDecideClickCount() ? 5
                                                           : 0;
    if (statePWR)
    {
        M5_LOGI("BtnPWR:%s  count:%d", names[statePWR], M5.BtnPWR.getClickCount());
        M5.Display.fillRect(w * 0, 0, w - 1, h, colors[statePWR]);
    }

    const int stateA = M5.BtnA.wasHold()               ? 1
                       : M5.BtnA.wasClicked()          ? 2
                       : M5.BtnA.wasPressed()          ? 3
                       : M5.BtnA.wasReleased()         ? 4
                       : M5.BtnA.wasDecideClickCount() ? 5
                                                       : 0;
    if (stateA)
    {
        M5_LOGI("BtnA:%s  count:%d", names[stateA], M5.BtnA.getClickCount());
        M5.Display.fillRect(w * 1, 0, w - 1, h, colors[stateA]);
    }

    const int stateB = M5.BtnB.wasHold()               ? 1
                       : M5.BtnB.wasClicked()          ? 2
                       : M5.BtnB.wasPressed()          ? 3
                       : M5.BtnB.wasReleased()         ? 4
                       : M5.BtnB.wasDecideClickCount() ? 5
                                                       : 0;
    if (stateB)
    {
        M5_LOGI("BtnB:%s  count:%d", names[stateB], M5.BtnB.getClickCount());
        M5.Display.fillRect(w * 2, 0, w - 1, h, colors[stateB]);
    }

    const int stateC = M5.BtnC.wasHold()               ? 1
                       : M5.BtnC.wasClicked()          ? 2
                       : M5.BtnC.wasPressed()          ? 3
                       : M5.BtnC.wasReleased()         ? 4
                       : M5.BtnC.wasDecideClickCount() ? 5
                                                       : 0;
    if (stateC)
    {
        M5_LOGI("BtnC:%s  count:%d", names[stateC], M5.BtnC.getClickCount());
        M5.Display.fillRect(w * 3, 0, w - 1, h, colors[stateC]);
    }

    const int stateEXT = M5.BtnEXT.wasHold()               ? 1
                         : M5.BtnEXT.wasClicked()          ? 2
                         : M5.BtnEXT.wasPressed()          ? 3
                         : M5.BtnEXT.wasReleased()         ? 4
                         : M5.BtnEXT.wasDecideClickCount() ? 5
                                                           : 0;
    if (stateEXT)
    {
        M5_LOGI("BtnEXT:%s  count:%d", names[stateEXT], M5.BtnEXT.getClickCount());
        M5.Display.fillRect(w * 4, 0, w - 1, h, colors[stateEXT]);
    }

    M5.Display.endWrite();
}
