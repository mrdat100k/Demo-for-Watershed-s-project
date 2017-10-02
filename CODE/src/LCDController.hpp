
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
		second(0), minute(0), hour(0),
		timer_is_on(true), /*TODO: kiem tra lai */
		cursor_pos_col{ 0, 53, 86 },
		cursor_pos_row{ 18, 30, 42, 54 }		
	{
		
		I2C_object = new I2CPreInit(I2C_SDA, I2C_SCL);
		lcd_object = new Adafruit_SSD1306_I2c(I2C_object, NC);  /*TODO: NC o dau ra ???*/

		lcd_object.begin();

	}

	void showLogo(uint8_t* watershed_logo_data){
		lcd_object.drawBitmap(0, 6, watershed_logo_data, 128, 48, WHITE);
		lcd_object.setTextCursor(0, 0);
		lcd_object.display();
	}
	void setPVVolt(float value){
		pv_volt = value;
	}

	void setPVCurr(float value){
		pv_volt = value;
	}

	void setPVPower(float value){
		pv_volt = value;
	}

	void setPVEnergy(float value){
		pv_volt = value;
	}

	void setBattVolt(float value){
		battery_volt = value;
	}

	void setBattCurr(float value){
		battery_volt = value;
	}

	void setBattPower(float value){
		battery_volt = value;
	}

	void setBattEnergy(float value){
		battery_volt = value;
	}
	
	//************************************
	// Method:    LCDController::composeScreen
	// Description: This function will update LCD with each scenario
	// Access:    private 
	// Returns:   void
	// Parameter: int screen_index
	// TODO: viet not ham nay
	//************************************	
	void  updateScreen(int screen_index){

		char buff[12]; /*Data buffer*/
		lcd_object->clearDisplay();


		


		/* Update screen contents */
		switch (screen_index)
		{
		case(0) : {

					  //TODO: viet not
					  break;
		}
		case(1) : {
					  //TODO: viet not
					  break;
		}
		case(2) : {
					  writeAtPosition(0, "Battery Charge Info");
					  writeAtPosition(1, "Bat Voltage");
					  writeAtPosition(4, "Bat Current");
					  writeAtPosition(7, "Power");
					  writeAtPosition(10, "Energy");
					  /* Update timer*/
					  sprintf(buff, "%02d:%02d:%02d", hour, min, second);

					  /* Update battery current*/
					  sprintf(buff, "%2.1f mA ", battery_curr);
					  writeAtPosition(5, buff);

					  /* Update battery voltage*/
					  sprintf(buff, "%2.1f V ", battery_volt);
					  writeAtPosition(2, buff);

					  /* Update battery power*/
					  sprintf(buff, "%2.1fW ", battery_power);
					  writeAtPosition(8, buff);

					  /* Update battery energy */
					  sprintf(buff, "%3.1fWh ", energy);
					  writeAtPosition(11, buff);
					  break;
		}
		default:
			break;
		}

		lcd_object->display();
	}

	void setTimer(int hour, int minute, int second){
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}

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

	char* screen_buffer[];
	char* screen_templates[3];

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
	void writeAtPosition(int pos, const char* data)
	{
		lcd_object->setTextCursor(cursor_pos_col[pos], cursor_pos_row[pos]);
		lcd_object->printf("%s", data);
		lcd_object->setTextCursor(0, 0);
	}

	
	


};