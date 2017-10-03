#include <mbed.h>
#include "RTC_Timer.hpp"
#include "IOPins.h"
class KeyboardController{
public:
	KeyboardController(RTC_Timer* timer)
	{
	    timer_ptr = timer;
	    set_button = new InterruptIn(SELECT_BUTTON_PIN);
	    select_button = new InterruptIn(SELECT_BUTTON_PIN);
	}

	void Init()
	{
      set_button -> fall(&OnSetButtonPress_fall_isr);
	    select_button -> fall(&OnSelectButtonPress_fall_isr);
	    set_button -> rise(&OnSetButtonPress_rise_isr);
	}
	uint8_t getMenuIndex()
	{
	    return menu_index;
	}
	static void attimeout()
		{
				menu_index = 0;
		}
	static void OnSetButtonPress_fall_isr()
		{
			set_button -> disable_irq();

			time_out_s.attach(&attimeout, 15);

			wait_ms(20);

			if (menu_index== 1 || menu_index == 2)
			{
				time_start = timer_ptr -> GetSecond_s();
				timer_ptr -> ChangeState();
			}

			set_button -> enable_irq();
		}


	static void OnSetButtonPress_rise_isr()
		{
			set_button -> disable_irq();
			time_out_s.attach(&attimeout, 15);
			wait_ms(20);
			if ((menu_index == 1) || (menu_index == 2))
			{
				time_stop = timer_ptr -> GetSecond_s();
				time_press = time_stop - time_start;
			}
			if(time_press > 2)
			{
				timer_ptr -> Reset();
				time_press = 0;
			}
			set_button -> enable_irq();
		}

	static void OnSelectButtonPress_fall_isr(){
			select_button -> disable_irq();
			time_out_s.attach(&attimeout, 15);
			wait_ms(20);
			menu_index ++;
			if (menu_index >= 3)
			{
				menu_index = 0;
			}

			select_button-> enable_irq();
		}

private:

  static RTC_Timer* timer_ptr;
  static InterruptIn* set_button;
  static InterruptIn* select_button;
	static Timeout time_out_s;
	static uint8_t menu_index;
	static uint32_t time_start, time_stop, time_press;

};
