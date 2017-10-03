class Timer{
public:
	Timer() :timer_state(false), second(0), minute(0), hour(0), day(0){

	}

	void Reset(){
		timer_state = true;
		second = 0;
		minute = 0;
		hour = 0;
		day = 0;
	}

	void Pause(){
		timer_state = false;
	}

	void Resume(){
		timer_state = true;
	}

	bool GetTimerState(){
		return timer_state;
	}
	void Update(){
		if (timer_state)
		{
			/* Update timer*/
			uint32_t seconds = time(NULL); /*TODO: bo sung header cho ham time */
			second = seconds % 60;
			minute = seconds % 3600 / 60;
			hour = seconds % 86400 / 3600;
		}
	}

	int GetSecond(){
		return second;
	}

	int GetMinute(){
		return minute;
	}

	int GetHour(){
		return hour;
	}





private:
	bool timer_state;
	int second, minute, hour, day;
	
};