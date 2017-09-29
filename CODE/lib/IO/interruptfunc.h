#ifndef _INTFUNC_H
#define _INTFUNC_H
#include<mbed.h>
#include<iopin.h>
uint8_t g_mode=0;
Timeout g_time_out_s;
time_t g_time_1_s; //chuc nang ?
time_t g_time_2_s; // chuc nang?
InterruptIn g_button_set(set);
InterruptIn g_button_select(select);
bool g_timer_on_1_=true; //
bool  g_timer_on_2_=true;//
void set_mode_when_timeout() 
{
    g_mode=0;
}

void press_button_to_seclect()
{
    g_button_select.disable_irq();
    g_time_out_s.attach(&set_mode_when_timeout, 15);
    wait_ms(20);
    g_mode++;
    if(g_mode >= 3) 
    {
        g_mode=0;
    }
  
    press_button.enable_irq();
}

void press_button_to_set() 
{
    btn_Set.disable_irq();
    timeout.attach(&attimeout, 15);
    wait_ms(20);
    if(mode == 1)
    {
        timerOn1=!timerOn1; 
        time1=time(NULL);
    }
  
    if(mode == 2) 
    { 
        timerOn2=!timerOn2; 
        time1=time(NULL);
    }
  
    btn_Set.enable_irq();
}

void btn_press()
{
    btn_Set.disable_irq();
    timeout.attach(&attimeout, 15);
    wait_ms(20);
    if((mode == 1) || (mode == 2))
    {
        time2=time(NULL);
    }
  
    if((time2-time1) >= 2)
    {
        set_time(0); 
        if(mode == 1) 
        {
            timerOn1 =! timerOn1; 
            if(mode == 2) 
            {
              timerOn2 =! timerOn2;
            }
        }
    }
  
    btn_Set.enable_irq();
}
#endif
