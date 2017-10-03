#include <mbed.h>
#include <IOPins.h>
#include <LCDController.h>
#include <INAReader.hpp>
#include <RTC_Timer.hpp>
#include <KeyboardController.hpp>
#include <RelayController.hpp>
LCDController lcd_controller;
INAReader ina_reader(I2C_SDA, I2C_SCL);
RelayController relay;
RTC_Timer rtc_timer;
KeyboardController keyboard(&rtc_timer);
void Init();
int main(int argc, char** argv) {

    // put your setup code here, to run once:
    Init();
    while(1) {
        // put your main code here, to run repeatedly:
        ina_reader.Scan();
        rtc_timer.Update();
        lcd_controller.updateScreen(keyboard.getMenuIndex());
    }
}
void Init(){
    keyboard.Init();
}
