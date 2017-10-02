#include <....>
#include "LCDController.hpp"
#include "INAReader.hpp"
#include "KeyboardController.hpp"
#include "RelayController.hpp"
#include "Timer.hpp"

LCDController lcd_controller;
INAReader ina_reader;
KeyboardController keyboard;
RelayController relay;
Timer timer;

void Init();


int main(int argc, char** argv){
	int lcd_menu_state = 0; /*Menu position*/
	// Main loop
	while (true)
	{
		keyboard.Scan();
		ina_reader.Scan();
		timer.Update();

		if (/*TODO: Pressing button*/){
			lcd_menu_state++;
			lcd_menu_state = lcd_menu_state % 3; /*Go to first menu*/
		}

		/*TODO: update sensor value */
		lcd_controller.setBattVolt(/**/);
		/*......
		........
		......
		*/

		if (timer.GetState()){
			// Update timer value
			lcd_controller.setTime(timer.GetHour(), timer.GetMinute(), timer.GetSecond());
		}

		lcd_controller.updateScreen();


		/*TODO Control relay*/
		if (/* TODO: current is larger than value*/){
			relay.ChangeState();
		}
	}
}


void Init(){

	ina_reader.Init();
	keyboard.Init();
};