
/*!
 * \file LCDController.hpp
 * \summary This class contains driver for controlling LCD
 *
 * \author 
 *
 * \date October 2017
 *
 * 
 */

#include "logo.h"
#include <Adafruit_SSD1306.h>


class LCDController{

public:


	//************************************
	// Method:    LCDController::LCDController
	// Description:  LCDController constructor, initialize all measuring variables to 0
	// Access:    public 
	// Returns:   
	// Qualifier: : pv_volt(0), pv_curr(0), pv_power(0), pv_energy(0), bat_volt(0), bat_curr(0), bat_power(0), bat_energy(0)
	//************************************
	LCDController() :
		pv_volt(0), pv_curr(0), pv_power(0), pv_energy(0),
		bat_volt(0), bat_curr(0), bat_power(0), bat_energy(0),
		power_level(0), energy(0),
		second(0), minute(0), hour(0),state(fail);
		//timer_is_on(true), /*TODO: kiem tra lai */
		cursor_pos_col{ 0, 53, 86 },
		cursor_pos_row{ 18, 30, 42, 54 }		
	{
		
		I2C_object = new I2CPreInit(I2C_SDA, I2C_SCL);
		lcd_object = new Adafruit_SSD1306_I2c(I2C_object, NC);  /*TODO: NC o dau ra ???*/

		lcd_object.begin();

	}

	void showLogo(uint8_t* watershed_logo_data);

	void setPVVolt(float value);

	void setPVCurr(float value);

	void setPVPower(float value);

	void setPVEnergy(float value);

	void setBattVolt(float value);

	void setBattCurr(float value);

	void setBattPower(float value);

	void setBattEnergy(float value);
	
	//************************************
	// Method:    LCDController::composeScreen
	// Description: This function will update LCD with each scenario
	// Access:    private 
	// Returns:   void
	// Parameter: int screen_index
	// TODO: viet not ham nay
	//************************************	
	void  updateScreen(int screen_index);

	//void setTimer(int hour, int minute, int second);

private:
	I2CPreInit* I2C_object;	/* LCD-ARM Communication object */
	Adafruit_SSD1306_I2c* lcd_object;/* LCD object from Adafruit driver */
	float pv_volt;
	float pv_curr;
	float pv_power;
	float pv_energy;
	float battery_volt;
	float battery_curr;
	float battery_power;
	float battery_energy;

	float power_level;
	float energy;

	float second, minute, hour;

	//char* screen_buffer[];
	//char* screen_templates[3];

	int cursor_pos_col[3],cursor_pos_row[4]; //cursor's position for each col/row

	
	//************************************
	// Method:    LCDController::writeAtPosition
	// Description:  write any text at specific location (x,y) on the screen
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: int16_t posX
	// Parameter: int16_t posY
	// Parameter: const char * data
	//************************************
	void writeAtPosition(int pos, const char* data);

	
	


};
