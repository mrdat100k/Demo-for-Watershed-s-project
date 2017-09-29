// test editting
int foo=0;

#include <mbed.h>
#include <lcd_menu.hpp>
#include <INA219.hpp>
#include <iopin.h>
#include <interruptfunc.h>
#include <logo.h>
DigitalOut myled(LED1);
extern InterruptIn g_setting_button;
extern InterruptIn g_selecting_button;
DigitalOut relay(InverterEnable);
INA219 sensor1(I2C_SDA, I2C_SCL);
INA219 sensor2(I2C_SDA, I2C_SCL, 0x41);
extern uint8_t g_mode;
extern bool g_timer_on_1_s;
extern bool g_timer_on_2_s;
uint8_t g_sec_;
uint8_t g_min_;
uint8_t g_hour_;
extern Adafruit_SSD1306_I2c gOled;

void get_data_ina(INA219* sensor, float* volt, float* curr, float* power)
{
    *volt=sensor->read_bus_voltage();
    *curr=sensor->read_current_mA();
    *power=sensor->read_power_mW();
}

int main() 
{
    float pvvolt;
    float pvCurr;
    float pvPower;
    float pvEnergy;
    float batVolt;
    float batCurr;
    float batPower;
    float batEnergy;
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
    g_setting_button.disable_irq();
    g_selecting_button.disable_irq();
    g_setting_button.fall(&btn_set);
    g_selecting_button.fall(&btn_select);
    g_setting_button.rise(&btn_press);
    g_setting_button.enable_irq();
    g_selecting_button.enable_irq();
    wait(2);
    set_time(0);

    while(1)
    {
        // put your main code here, to run repeatedly:
        uint32_t seconds = time(NULL);
        g_sec_ = seconds % 60;
        g_min_ = seconds % 3600 / 60;
        g_hour_ = seconds % 86400 / 3600;
        get_data_ina(&sensor1, &batVolt, &batCurr,  &batPower);
        get_data_ina(&sensor, &pvVolt, &pvCurr, &pvPower);
        
       = batPower / 1000  * (float)seconds / 3600;
        pvEnergy = pvPower / 1000 * (float)seconds / 3600;
        if(g_mode == 0)
        {
            menu1_display(true, batVolt / 1000, true, true);
        }
     
        if(g_mode == 1)
        {
           menu2_display(pvVolt / 1000, pvCurr, pvPower / 1000, pvEnergy, timerOn1, hour_, min_, sec_);
        }
     
        if(g_mode == 2)
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
