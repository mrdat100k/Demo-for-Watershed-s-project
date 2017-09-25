#ifndef _LCD_MENU_H_
#define _LCD_MENU_H_
#include <Adafruit_SSD1306.h>
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


class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);
        start();
    };
};
I2CPreInit gI2C(PB_7,PB_6);
Adafruit_SSD1306_I2c gOled(gI2C,NC);
void write_position(int16_t posX, int16_t posY,const char* data)
{
  gOled.setTextCursor(posX,posY);
  gOled.printf("%s",data);
  gOled.setTextCursor(0,0);
}
void menu1_display(bool _charge, float _batVolt, bool _DCOn, bool _ACOn)
{
  char buff[10];
  sprintf(buff,"%2.1f V ",_batVolt);
  gOled.clearDisplay();
  write_position(pos_menuX,pos_menuY,"MAIN MENU");
  write_position(position1X,position1Y,"Charge");
  write_position(position4X,position4Y,"Battery");
  write_position(position7X,position7Y,"DC On");
  write_position(position10X,position10Y,"AC On");
  write_position(position5X,position5Y,buff);
  if(_charge) write_position(position2X,position2Y,"Yes");
  else  write_position(position2X,position2Y,"No ");
  if(_DCOn) write_position(position8X,position8Y,"Yes");
  else write_position(position8X,position8Y,"No ");
  if(_ACOn) write_position(position11X,position11Y,"Yes");
  else write_position(position11X,position11Y,"No ");
  if(_DCOn&&_ACOn) write_position(position3X,position3Y,"DC/AC");
  else if(_DCOn&&!_ACOn)  write_position(position3X,position3Y,"DC   ");
  else  write_position(position3X,position3Y,"     ");
  gOled.display();
}
void menu2_display(float _volt, float _current, float _Power, float _Energy, bool _timerOn, uint8_t _hour, uint8_t _min, uint8_t _sec)
{
  char buff[12];
  if(_current<0) _current=0;
  if(_volt<0) _volt=0;
  gOled.clearDisplay();
  write_position(pos_menuX,pos_menuY,"PV Charge Info");
  write_position(position1X,position1Y,"PV Voltage");
  write_position(position4X,position4Y,"PV Current");
  write_position(position7X,position7Y,"Power");
  write_position(position10X,position10Y,"Energy");

  sprintf(buff,"%2.1f mA ",_current);
  write_position(position5X+20,position5Y,buff);
  sprintf(buff,"%2.1f V ",_volt);
  write_position(position2X+20,position2Y,buff);
  sprintf(buff,"%2.1fW ",_Power);
  write_position(position8X,position8Y,buff);
  sprintf(buff,"%3.1fWh ",_Energy);
  write_position(position11X,position11Y,buff);
  if(_sec<10&&_min<10) sprintf(buff,"%u:0%u:0%us",_hour,_min,_sec);
  else if(_sec<10&&_min>=10) sprintf(buff,"%u:%u:0%us",_hour,_min,_sec);
  else if(_sec>=10&&_min<10) sprintf(buff,"%u:0%u:%us",_hour,_min,_sec);
  else sprintf(buff,"%u:%u:%us",_hour,_min,_sec);
  if(_timerOn)
  {
    write_position(position9X,position9Y,"TimerON ");
    write_position(position12X,position12Y,buff);
  }
  else write_position(position9X,position9Y,"TimerOFF");
  gOled.display();
}
void menu3_display(float _volt, float _current, float _Power, float _Energy, bool _timerOn, uint8_t _hour, uint8_t _min, uint8_t _sec)
{
  char buff[12];
  if(_current<0) _current=0;
  if(_volt<0) _volt=0;
  gOled.clearDisplay();
  write_position(pos_menuX,pos_menuY,"Battery Charge Info");
  write_position(position1X,position1Y,"Bat Voltage");
  write_position(position4X,position4Y,"Bat Current");
  write_position(position7X,position7Y,"Power");
  write_position(position10X,position10Y,"Energy");
  sprintf(buff,"%2.1f mA ",_current);
  write_position(position5X+20,position5Y,buff);
  sprintf(buff,"%2.1f V ",_volt);
  write_position(position2X+20,position2Y,buff);
  sprintf(buff,"%2.1fW ",_Power);
  write_position(position8X,position8Y,buff);
  sprintf(buff,"%3.1fWh ",_Energy);
  write_position(position11X,position11Y,buff);
  if(_sec<10&&_min<10) sprintf(buff,"%u:0%u:0%us",_hour,_min,_sec);
  else if(_sec<10&&_min>=10) sprintf(buff,"%u:%u:0%us",_hour,_min,_sec);
  else if(_sec>=10&&_min<10) sprintf(buff,"%u:0%u:%us",_hour,_min,_sec);
  else sprintf(buff,"%u:%u:%us",_hour,_min,_sec);
  if(_timerOn)
  {
    write_position(position9X,position9Y,"TimerON ");
    write_position(position12X,position12Y,buff);
  }
  else write_position(position9X,position9Y,"TimerOFF");
  gOled.display();
}
#endif
