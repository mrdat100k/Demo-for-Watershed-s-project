#ifndef _INTFUNC_H
#define _INTFUNC_H
#include<mbed.h>
#include<iopin.h>
uint8_t mode=0;
Timeout timeout;
time_t time1, time2;
InterruptIn btn_Set(set);
InterruptIn btn_Select(select);
bool timerOn1=true;
bool timerOn2=true;
void attimeout()
{
  mode=0;
}
void btn_select()
{
  btn_Select.disable_irq();
  timeout.attach(&attimeout,15);
  wait_ms(20);
  mode++;
  if(mode>=3) mode=0;
  btn_Select.enable_irq();
}
void btn_set()
{
  btn_Set.disable_irq();
  timeout.attach(&attimeout,15);
  wait_ms(20);
  if(mode==1) {timerOn1=!timerOn1; time1=time(NULL);}
  if(mode==2) {timerOn2=!timerOn2; time1=time(NULL);}
  btn_Set.enable_irq();
}
void btn_press()
{
  btn_Set.disable_irq();
  timeout.attach(&attimeout,15);
  wait_ms(20);
  if(mode==1||mode==2) time2=time(NULL);
  if((time2-time1)>=2)   {set_time(0); if(mode==1) timerOn1=!timerOn1; if(mode==2) timerOn2=!timerOn2;}
  btn_Set.enable_irq();
}
#endif
