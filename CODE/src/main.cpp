// test editting
int foo=0;

#include <mbed.h>
#include <lcd_menu.hpp>
#include <INA219.hpp>
#include <iopin.h>
#include <interruptfunc.h>
#include <logo.h>
DigitalOut myled(LED1);
extern InterruptIn btn_Set;
extern InterruptIn btn_Select;
DigitalOut relay(InverterEnable);
INA219 sensor1(I2C_SDA, I2C_SCL);
INA219 sensor2(I2C_SDA, I2C_SCL, 0x41);
extern uint8_t mode;
extern bool timerOn1;
extern bool timerOn2;
uint8_t sec_, min_, hour_;
extern Adafruit_SSD1306_I2c gOled;

void getDataINA(INA219* sensor, float* volt, float* curr, float* power)
{
    *volt=sensor->read_bus_voltage();
    *curr=sensor->read_current_mA();
    *power=sensor->read_power_mW();
}

int main() 
{
    float pvVolt, pvCurr, pvPower, pvEnergy, batVolt, batCurr, batPower, batEnergy;
    // put your setup code here, to run once:
    relay.write(0);
    wait_ms(300);
    gOled.begin();
    gOled.clearDisplay();
    gOled.setTextCursor(0, 0);
    gOled.drawBitmap(0, 6, watershedlogo, 128, 48, WHITE);
    gOled.setTextCursor(0, 0);
    gOled.display();
    sensor1.calibrate_32v_3200A();
    sensor2.calibrate_32v_3200A();
    btn_Set.disable_irq();
    btn_Select.disable_irq();
    btn_Set.fall(&btn_set);
    btn_Select.fall(&btn_select);
    btn_Set.rise(&btn_press);
    btn_Set.enable_irq();
    btn_Select.enable_irq();
    wait(2);
    set_time(0);

    while(1)
    {
        // put your main code here, to run repeatedly:
        uint32_t seconds = time(NULL);
        sec_ = seconds % 60;
        min_ = seconds % 3600 / 60;
        hour_ = seconds % 86400 / 3600;
        getDataINA(&sensor1, &batVolt, &batCurr,  &batPower);
        getDataINA(&sensor, &pvVolt, &pvCurr, &pvPower);
        batEnergy = batPower / 1000  * (float)seconds / 3600;
        pvEnergy = pvPower / 1000 * (float)seconds / 3600;
        if(mode == 0)
        {
            menu1_display(true, batVolt / 1000, true, true);
        }
     
        if(mode == 1)
        {
           menu2_display(pvVolt / 1000, pvCurr, pvPower / 1000, pvEnergy, timerOn1, hour_, min_, sec_);
        }
     
        if(mode == 2)
        {
           menu3_display(batVolt /1000, batCurr, batPower / 1000, batEnergy, timerOn2, hour_, min_, sec_);
        }
     
        if(batCurr < 50)
        {
           relay.write(1);
        }
        else
        {
           relay.write(0);
        }
     
        myled =! myled;
        wait_ms(100);
    }
}
