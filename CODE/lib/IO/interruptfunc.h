/** @file iopin.h
*
* @brief This file include interrupt service routine for buttons.
* 
* @par
* COPYRIGHT NOTICE: (c) 2017 MANDEVICES GROUP, HUST.
*/
#ifndef _INTFUNC_H
#define _INTFUNC_H

#ifdef __cplusplus
extern “C” {
#endif
/******************************************************************************
INCLUDES
******************************************************************************/
#include<mbed.h>
#include<iopin.h>
/******************************************************************************
GLOBAL VARIABLES
******************************************************************************/
uint8_t g_mode=0;
Timeout g_time_out_s;
time_t g_time_start_s;
time_t g_time_stop_s; 
InterruptIn g_setting_button(set);
InterruptIn g_selecting_button(select);
bool g_timer_on_1 = true; 
bool g_timer_on_2 = true;
/******************************************************************************
* DESCRIPTION: the timeout service routine, when timeout reset mode to switch back the main menu
* @author:
*
* @version: v1.0.0
* @param:
* NONE
* @return: NONE
* @see:
* .../lib/IO/interruptfunc.h
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
void set_mode_when_timeout() 
{
    g_mode = 0;
}

/******************************************************************************
* DESCRIPTION: the Interrupt service routine of fall interrupt when press the select button
* @author:
* 
* @version: v1.0.0
* @param:
* NONE
* @return: NONE
* @see:
* .../lib/IO/interruptfunc.h
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
static void fall_select_btn_isr()
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
/******************************************************************************
* DESCRIPTION: the Interrupt service routine of fall interrupt when press the set button
* @author:
* 
* @version: v1.0.0
* @param:
* NONE
* @return: NONE
* @see:
* .../lib/IO/interruptfunc.h
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
static void fall_set_btn_isr() 
{
    btn_Set.disable_irq();
    timeout.attach(&attimeout, 15);
    wait_ms(20);
    if(mode == 1)
    {
        g_timer_on_1 =! g_timer_on_1; 
        g_time_start_s = time(NULL);
    }
  
    if(mode == 2) 
    { 
        g_timer_on_1 =! g_timer_on_1; 
        g_time_start_s = time(NULL);
    }
  
    btn_Set.enable_irq();
}
/******************************************************************************
* DESCRIPTION: the Interrupt service routine of rise interrupt when press the set button
* @author:
* 
* @version: v1.0.0
* @param:
* NONE
* @return: NONE
* @see:
* .../lib/IO/interruptfunc.h
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
static void rise_set_btn_isr()
{
    btn_Set.disable_irq();
    timeout.attach(&attimeout, 15);
    wait_ms(20);
    if((mode == 1) || (mode == 2))
    {
        g_time_stop_s = time(NULL);
    }
  
    if((g_time_stop_s - g_time_start_s) >= 2)
    {
        set_time(0); 
        if(mode == 1) 
        {
            g_timer_on_1 =! g_timer_on_1; 
            if(mode == 2) 
            {
              g_timer_on_2 =! g_timer_on_2;
            }
        }
    }
  
    btn_Set.enable_irq();
}
#endif /* _INTFUNC_H */
