/******************************************************************************
* @file main.cpp
* @author MANDEVICES GROUP
* @version V1.0.1
* @date 29/09/2017
* @brief
******************************************************************************/
/******************************************************************************
INCLUDES
******************************************************************************/
#include <mbed.h>
#include <lcd_menu.hpp>
#include <INA219.hpp>
#include <iopin.h>
#include <interruptfunc.h>
#include <logo.h>
/******************************************************************************
GLOBAL VARIABLES
******************************************************************************/
DigitalOut myled(LED1);
extern InterruptIn g_setting_button;
extern InterruptIn g_selecting_button;
DigitalOut relay(InverterEnable);
INA219 bat_measure_sensor(I2C_SDA, I2C_SCL, 0x40);
INA219 pv_measure_sensor(I2C_SDA, I2C_SCL, 0x41);
extern uint8_t g_mode;
extern bool g_timer_on_1;
extern bool g_timer_on_2;
uint8_t g_sec_;
uint8_t g_min_;
uint8_t g_hour_;
extern Adafruit_SSD1306_I2c gOled;
/******************************************************************************
GLOBAL FUNCTIONS
******************************************************************************/
void get_data_ina(INA219* sensor, float* volt, float* curr, float* power);
/******************************************************************************
DATA TYPE DEFINE
******************************************************************************/
/******************************************************************************
PRIVATE VARIABLES
******************************************************************************/
/******************************************************************************
LOCAL FUNCTIONS
******************************************************************************/
/*****************************************************************************/
/**
* @brief:
* @param:
* @retval:
* @author: 
* @created: 29/09/2017
* @version:
* @reviewer:
*/

/******************************************************************************
* DESCRIPTION: Function to get voltage, current, power measured by INA219 
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* INA219* pSensor : the pointer of INA219 object
* float* pVolt: the pointer of voltage varible
* float* pCurr: the pointer of current varible 
* float* pPower: the pointer of power varible
* @return: NONE
* @see:
* .../src/main.cpp
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
void get_data_ina(INA219* sensor, float* volt, float* curr, float* power)
{
    *volt = sensor -> read_bus_voltage();
    *curr = sensor -> read_current_mA();
    *power = sensor -> read_power_mW();
}

int main() 
{
    float pv_volt;
    float pv_curr;
    float pv_power;
    float pv_energy;
    float bat_volt;
    float bat_curr;
    float bat_power;
    float bat_energy;
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
    g_setting_button.fall(&fall_set_btn_isr);
    g_selecting_button.fall(&fall_select_btn_isr);
    g_setting_button.rise(&rise_set_btn_isr);
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
        get_data_ina(&bat_measure_sensor, &bat_volt, &bat_curr,  &bat_power);
        get_data_ina(&pv_measure_sensor, &pv_volt, &pv_curr, &pv_power);
        
        bat_energy = bat_power / 1000  * (float)seconds / 3600;
        pv_energy = pv_power / 1000 * (float)seconds / 3600;
        if(g_mode == 0)
        {
            menu1_display(true, bat_volt / 1000, true, true);
        }
     
        if(g_mode == 1)
        {
           menu2_display(pv_volt / 1000, pv_curr, pv_power / 1000, pv_energy, g_timer_on_1, hour_, min_, sec_);
        }
     
        if(g_mode == 2)
        {
           menu3_display(bat_volt /1000, bat_curr, bat_power / 1000, bat_energy, g_timer_on_2, hour_, min_, sec_);
        }
     
        if(bat_curr < 50)
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
