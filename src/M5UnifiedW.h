#pragma once

// M5Wokwi - minimal Arduino-compatible shim for emulating M5Unified APIs on Wokwi.
// Documentation: https://github.com/tanakamasayuki/M5Wokwi

#include <Arduino.h>
#include <LovyanGFX.hpp>

// Provide common TFT color definitions if they are missing.
#ifndef TFT_BLACK
#define TFT_BLACK 0x0000
#endif
#ifndef TFT_WHITE
#define TFT_WHITE 0xFFFF
#endif
#ifndef TFT_RED
#define TFT_RED 0xF800
#endif
#ifndef TFT_GREEN
#define TFT_GREEN 0x07E0
#endif
#ifndef TFT_BLUE
#define TFT_BLUE 0x001F
#endif
#ifndef TFT_YELLOW
#define TFT_YELLOW 0xFFE0
#endif
#ifndef TFT_CYAN
#define TFT_CYAN 0x07FF
#endif

namespace m5wokwi
{
    enum class epd_mode_t : uint8_t
    {
        epd_fastest = 0,
        epd_quality,
        epd_text,
    };

    class LGFX : public lgfx::LGFX_Device
    {
    public:
        LGFX()
        {
            auto bus_cfg = _bus.config();
            bus_cfg.spi_host = VSPI_HOST;
            bus_cfg.spi_mode = 0;
            bus_cfg.freq_write = 40000000;
            bus_cfg.freq_read = 16000000;
            bus_cfg.dma_channel = SPI_DMA_CH_AUTO;
            bus_cfg.pin_sclk = 18;
            bus_cfg.pin_mosi = 23;
            bus_cfg.pin_miso = 19;
            bus_cfg.pin_dc = 2;
            _bus.config(bus_cfg);
            _panel.setBus(&_bus);

            auto panel_cfg = _panel.config();
            panel_cfg.pin_cs = 5;
            panel_cfg.pin_rst = 16;
            panel_cfg.pin_busy = -1;
            panel_cfg.panel_width = 320;
            panel_cfg.panel_height = 240;
            panel_cfg.offset_x = 0;
            panel_cfg.offset_y = 0;
            panel_cfg.memory_width = 320;
            panel_cfg.memory_height = 240;
            panel_cfg.offset_rotation = 0;
            _panel.config(panel_cfg);

            auto light_cfg = _light.config();
            light_cfg.pin_bl = -1;
            _light.config(light_cfg);
            _panel.setLight(&_light);

            setPanel(&_panel);
        }

    private:
        lgfx::Bus_SPI _bus;
        lgfx::Panel_ILI9341 _panel;
        lgfx::Light_PWM _light;
    };

    class Display : public LGFX
    {
    public:
        Display()
            : _initialized(false)
        {
        }

        void begin()
        {
            if (_initialized)
            {
                return;
            }
            init();
            setColorDepth(16);
            fillScreen(TFT_BLACK);
            _initialized = true;
        }

        uint8_t getRotation() const
        {
            return static_cast<uint8_t>(LGFX::getRotation());
        }

        int32_t width() const
        {
            return static_cast<int32_t>(LGFX::width());
        }

        int32_t height() const
        {
            return static_cast<int32_t>(LGFX::height());
        }

    private:
        epd_mode_t _epdMode;
        bool _initialized;
    };

    class Button
    {
    public:
        bool isPressed() const { return false; }
        bool wasPressed() { return false; }
        bool wasReleased() { return false; }
        bool wasClicked() { return false; }
        bool wasHold() { return false; }
        bool isHolding() const { return false; }
        bool wasDecideClickCount() { return false; }
        uint8_t getClickCount() const { return 0; }
    };
} // namespace m5wokwi

class M5WokwiClass
{
public:
    m5wokwi::Display Display;
    m5wokwi::Button BtnA;
    m5wokwi::Button BtnB;
    m5wokwi::Button BtnC;
    m5wokwi::Button BtnEXT;
    m5wokwi::Button BtnPWR;

    void begin()
    {
        if (!Serial)
        {
            Serial.begin(115200);
            delay(10);
        }
        Display.begin();
    }

    void update()
    {
        // TODO: poll Wokwi input state once backend is available.
    }

    void delay(uint32_t ms)
    {
        ::delay(ms);
    }
};

extern M5WokwiClass M5;

namespace m5wokwi
{
    // using ::epd_mode_t;
    using ::M5;
    using ::M5WokwiClass;
}
