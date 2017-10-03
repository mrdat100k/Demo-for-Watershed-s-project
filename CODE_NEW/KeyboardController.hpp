
class KeyboardController{
public:
	KeyboardController(Timer* timer):
	{
		timer_ptr = timer;
		g_set_button = new InterruptIn(SELECT_BUTTON_PIN);
		g_select_button = new InterruptIn(SELECT_BUTTON_PIN);
	}

	void Init(){

	}
private:

	void PressSetButtonFunction(){

	}


	void LongPressSetButtonFunction(){

	}

	void PressSelectButtonFunction(){
		g_select_button.disable_irq();
		g_time_out_s.attach(&set_mode_when_timeout, 15);
		wait_ms(20);
		g_mode++;
		if (g_mode >= 3)
		{
			g_mode = 0;
		}

		press_button.enable_irq();
	}

	Timer* timer_ptr;

	InterruptIn* g_set_button, g_select_button;
	Timeout g_time_out_s;
};