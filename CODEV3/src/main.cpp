#include <mbed.h>
#include <LCDController.h>

int main() {
  wait(2);
  LCDController test(&g_lcd_object);
    // put your setup code here, to run once:
//lcdcontroller.showLogo(watershed_logo_data);
    while(1) {
        // put your main code here, to run repeatedly:
        wait(5.0);
        test.showLogo();
        wait(5);
        test.updateScreen(2);
    }
}
