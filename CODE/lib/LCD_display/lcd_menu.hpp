/** @file lcd_menu.hpp
*
* @brief This is a library for format and display three menu.
* 
* @par
* COPYRIGHT NOTICE: (c) 2017 MANDEVICES GROUP, HUST.
*/
#ifndef _LCD_MENU_H_
#define _LCD_MENU_H_
/******************************************************************************
INCLUDES
******************************************************************************/
#include <Adafruit_SSD1306.h>
/******************************************************************************
DATA TYPE DEFINE
******************************************************************************/
#define pos_menuX 0
#define pos_menuY 0
#define position1X 0
#define position1Y 18
#define position2X 53
#define position2Y 18
#define position3X 86
#define position3Y 18
#define position4X 0
#define position4Y 30
#define position5X 53
#define position5Y 30
#define position6X 86
#define position6Y 30
#define position7X 0
#define position7Y 42
#define position8X 38
#define position8Y 42
#define position9X 80
#define position9Y 42
#define position10X 0
#define position10Y 54
#define position11X 38
#define position11Y 54
#define position12X 80
#define position12Y 54

/* an I2C sub-class that provides a constructed default */
class I2CPreInit : public I2C
{
    public:
        I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
        {
            frequency(400000);
            start();
        }
}

I2CPreInit gI2C(PB_7, PB_6);
Adafruit_SSD1306_I2c gOled(gI2C, NC);
/******************************************************************************
* DESCRIPTION: Function to write a string at position defined on screen 
* (hàm dùng để viết một chuỗi kí tự ra một vị trí trên màn hình)
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* int16_t posX: the latitude position
* int16_t posY: the longitude position
* const char* data: the string will print onto screen
* @return: NONE
* @see:
* .../lib/LCD_display/lcd_menu.hpp
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
void write_position(int16_t posX, int16_t posY, const char* data)
{
    gOled.setTextCursor(posX, posY);
    gOled.printf("%s", data);
    gOled.setTextCursor(0, 0);
}

/******************************************************************************
* DESCRIPTION: Function to display the main menu
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* bool _charge : a boolean varible mean batery charg Yes or No
* float _batVolt: the batery voltage
* bool _DCOn: a boolean varible mean the DC On Yes or No
* bool _ACOn: a boolean varible mean the AC (inverter) On Yes or No
* @return: NONE
* @see:
* .../lib/LCD_display/lcd_menu.hpp
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
void menu1_display(bool _charge, float _batVolt, bool _DCOn, bool _ACOn)
{
    char buff[10];
    sprintf(buff, "%2.1f V ", _batVolt);
    gOled.clearDisplay();
    write_position(pos_menuX, pos_menuY, "MAIN MENU");
    write_position(position1X, position1Y, "Charge");
    write_position(position4X, position4Y, "Battery");
    write_position(position7X, position7Y, "DC On");
    write_position(position10X, position10Y, "AC On");
    write_position(position5X, position5Y, buff);
    
    if(_charge)
    {
        write_position(position2X,position2Y,"Yes");
    }
    else
    {
        write_position(position2X,position2Y,"No ");
    }
    
    if(_DCOn)
    {
        write_position(position8X,position8Y,"Yes");
    }
    else
    {
        write_position(position8X,position8Y,"No ");
    }
    
    if(_ACOn)
    {
        write_position(position11X,position11Y,"Yes");
    }
    else
    {
        write_position(position11X,position11Y,"No ");
    }
    
    if(_DCOn && _ACOn)
    { 
        write_position(position3X,position3Y,"DC/AC");
    }
    else if(_DCOn && (!_ACOn))  
    {
        write_position(position3X,position3Y,"DC   ");
    }
    else
    {
        write_position(position3X,position3Y,"     ");
    }
    
    gOled.display();
}

/******************************************************************************
* DESCRIPTION: Function to display the PV charge Info menu
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* float _volt: the PV voltage
* float _current: the PV current
* float _Power: the PV power
* float _Energy: the PV energy
* bool _timerOn: control timer on/off
* uint8_t _hour: time
* uint8_t _min: time
* uint8_t _sec: time
* @return: NONE
* @see:
* .../lib/LCD_display/lcd_menu.hpp
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
void menu2_display(float _volt, float _current, float _Power, float _Energy, bool _timerOn, uint8_t _hour, uint8_t _min, uint8_t _sec)
{
    char buff[12];
    if(_current < 0)
    {
        _current=0;
    }
    
    if(_volt < 0)
    {
        _volt=0;
    }
    
    gOled.clearDisplay();
    write_position(pos_menuX, pos_menuY, "PV Charge Info");
    write_position(position1X, position1Y, "PV Voltage");
    write_position(position4X, position4Y, "PV Current");
    write_position(position7X, position7Y, "Power");
    write_position(position10X, position10Y, "Energy");
    sprintf(buff, "%2.1f mA ", _current);
    write_position(position5X+20, position5Y, buff);
    sprintf(buff, "%2.1f V ", _volt);
    write_position(position2X+20, position2Y, buff);
    sprintf(buff, "%2.1fW ", _Power);
    write_position(position8X, position8Y, buff);
    sprintf(buff, "%3.1fWh ", _Energy);
    write_position(position11X, position11Y, buff);
    
    if((_sec<10) && (_min<10))
    {
        sprintf(buff,"%u:0%u:0%us",_hour,_min,_sec);
    }
    else if((_sec<10) &&(_min>=10)) 
    {
        sprintf(buff, "%u:%u:0%us", _hour,_min,_sec);
    }
    else if((_sec>=10)&& (_min<10)) 
    {
        sprintf(buff,"%u:0%u:%us",_hour,_min,_sec);
    }
    else sprintf(buff,"%u:%u:%us",_hour,_min,_sec);
    if(_timerOn)
    {
      write_position(position9X,position9Y,"TimerON ");
      write_position(position12X,position12Y,buff);
    }
    else
    {
        write_position(position9X,position9Y,"TimerOFF");
    }
    
    gOled.display();
}

/******************************************************************************
* DESCRIPTION: Function to display the Battery charge Info menu
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* float _volt: the Battery voltage
* float _current: the Battery current
* float _Power: the Battery power
* float _Energy: the Battery energy
* bool _timerOn: control timer on/off
* uint8_t _hour: time
* uint8_t _min: time
* uint8_t _sec: time
* @return: NONE
* @see:
* .../lib/LCD_display/lcd_menu.hpp
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
void menu3_display(float _volt, float _current, float _Power, float _Energy, bool _timerOn, uint8_t _hour, uint8_t _min, uint8_t _sec)
{
    char buff[12];
    if((_current) < 0)
    {
        _current=0;
    }
    
    if((_volt) < 0) 
    {
        _volt=0;
    }
    
    gOled.clearDisplay();
    write_position(pos_menuX, pos_menuY, "Battery Charge Info");
    write_position(position1X, position1Y, "Bat Voltage");
    write_position(position4X, position4Y, "Bat Current");
    write_position(position7X, position7Y, "Power");
    write_position(position10X, position10Y, "Energy");
    sprintf(buff, "%2.1f mA ", _current);
    write_position(position5X+20, position5Y, buff);
    sprintf(buff, "%2.1f V ", _volt);
    write_position(position2X+20, position2Y, buff);
    sprintf(buff, "%2.1fW ", _Power);
    write_position(position8X, position8Y, buff);
    sprintf(buff, "%3.1fWh ", _Energy);
    write_position(position11X, position11Y, buff);
    
    if((_sec<10) && (_min<10))
    {
        sprintf(buff, "%u:0%u:0%us",_hour, _min,_sec);
    }
    else if((_sec<10) && (_min>=10))
    {
        sprintf(buff, "%u:%u:0%us", _hour, _min, _sec);
    }
    else if((_sec>=10) && (_min<10))
    {
        sprintf(buff, "%u:0%u:%us", _hour, _min, _sec);
    }
    else
    {
        sprintf(buff, "%u:%u:%us", _hour, _min, _sec);
    }  
    
    if(_timerOn)
    {
        write_position(position9X, position9Y, "TimerON ");
        write_position(position12X, position12Y, buff);
    }
    else
    {
        write_position(position9X, position9Y, "TimerOFF");
    }
    
    gOled.display();
}

#endif /* _LCD_MENU_H */
