#pragma once

// M5Wokwi - minimal Arduino-compatible shim for emulating M5Unified APIs on Wokwi.
// Documentation: https://github.com/tanakamasayuki/M5Wokwi

#include <Arduino.h>
#include <LovyanGFX.hpp>
#include "utility/Button_Class.hpp"

namespace m5wokwi
{
    class LGFX : public lgfx::LGFX_Device
    {
        lgfx::Panel_ILI9341 _panel_instance;
        lgfx::Bus_SPI _bus_instance;

    public:
        LGFX(void)
        {
            {
                auto cfg = _bus_instance.config();

                cfg.spi_host = VSPI_HOST;
                cfg.spi_mode = 0;
                cfg.freq_write = 40000000;
                cfg.freq_read = 16000000;
                cfg.spi_3wire = true;
                cfg.use_lock = true;
                cfg.dma_channel = SPI_DMA_CH_AUTO;
                cfg.pin_sclk = 18;
                cfg.pin_mosi = 23;
                cfg.pin_miso = 19;
                cfg.pin_dc = 2;
                _bus_instance.config(cfg);
                _panel_instance.setBus(&_bus_instance);
            }

            {
                auto cfg = _panel_instance.config();

                cfg.pin_cs = 15;
                cfg.pin_rst = 4;
                cfg.pin_busy = -1;

                cfg.panel_width = 240;
                cfg.panel_height = 320;
                cfg.offset_x = 0;
                cfg.offset_y = 0;
                cfg.offset_rotation = 5;
                cfg.dummy_read_pixel = 8;
                cfg.dummy_read_bits = 1;
                cfg.readable = true;
                cfg.invert = false;
                cfg.rgb_order = false;
                cfg.dlen_16bit = false;
                cfg.bus_shared = true;
                _panel_instance.config(cfg);
            }

            setPanel(&_panel_instance);
        }
    };

    class M5WokwiClass
    {
    public:
        m5wokwi::LGFX Display;
        m5::Button_Class &BtnA = _buttons[0];
        m5::Button_Class &BtnB = _buttons[1];
        m5::Button_Class &BtnC = _buttons[2];
        m5::Button_Class &BtnEXT = _buttons[3]; // CoreInk top button
        m5::Button_Class &BtnPWR = _buttons[4]; // CoreInk power button / AXP192 power button
        m5::Button_Class &getButton(size_t index) { return _buttons[index]; }
        m5::Button_Class &Buttons(size_t index) { return getButton(index); }

        void begin()
        {
            Serial.begin(115200);
            Display.init();
            pinMode(GPIO_NUM_12, INPUT_PULLUP); // BtnA
            pinMode(GPIO_NUM_13, INPUT_PULLUP); // BtnB
            pinMode(GPIO_NUM_14, INPUT_PULLUP); // BtnC
        };

        void update(void)
        {
            auto ms = lgfx::millis();
            _updateMsec = ms;
            uint_fast8_t use_rawstate_bits = 0;
            uint_fast8_t btn_rawstate_bits = 0;

            use_rawstate_bits = 0b00111;
            btn_rawstate_bits = (digitalRead(GPIO_NUM_12) << 0)    // gpio12 A
                                | (digitalRead(GPIO_NUM_13) << 1)  // gpio13 B
                                | (digitalRead(GPIO_NUM_14) << 2); // gpio14 C

            for (int i = 0; i < 5; ++i)
            {
                if (use_rawstate_bits & (1 << i))
                {
                    _buttons[i].setRawState(ms, btn_rawstate_bits & (1 << i));
                }
            }
        };

        void delay(uint32_t ms)
        {
            ::delay(ms);
        };

    private:
        m5::Button_Class _buttons[5];
        std::uint32_t _updateMsec = 0;
    };

} // namespace m5wokwi

extern m5wokwi::M5WokwiClass M5;

#define M5_LOGE(format, ...) Serial.printf("ERROR:" format "\r\n", ##__VA_ARGS__)
#define M5_LOGW(format, ...) Serial.printf("WARN:" format "\r\n", ##__VA_ARGS__)
#define M5_LOGI(format, ...) Serial.printf("INFO:" format "\r\n", ##__VA_ARGS__)
#define M5_LOGD(format, ...) Serial.printf("DEBUG:" format "\r\n", ##__VA_ARGS__)
#define M5_LOGV(format, ...) Serial.printf("VERBOSE:" format "\r\n", ##__VA_ARGS__)
