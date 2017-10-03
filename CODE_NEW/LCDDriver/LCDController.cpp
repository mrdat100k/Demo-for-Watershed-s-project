
#include "LCDController.h"


void LCDController::showLogo(uint8_t* watershed_logo_data){
		lcd_object.drawBitmap(0, 6, watershed_logo_data, 128, 48, WHITE);
		lcd_object.setTextCursor(0, 0);
		lcd_object.display();
	}
void LCDController::setPVVolt(float value){
		pv_volt = value;
	}

void LCDController::sLCDController::etPVCurr(float value){
		pv_volt = value;
	}

void LCDController::setPVPower(float value){
		pv_volt = value;
	}

void LCDController::setPVEnergy(float value){
		pv_volt = value;
	}

void LCDController::setBattVolt(float value){
		battery_volt = value;
	}

void LCDController::setBattCurr(float value){
		battery_volt = value;
	}

void LCDController::setBattPower(float value){
		battery_volt = value;
	}

void LCDController::setBattEnergy(float value){
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
void  LCDController::updateScreen(int screen_index){

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

void LCDController::setTimer(int hour, int minute, int second){
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}

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
void LCDController::LCDController::(int pos, const char* data)
	{
		lcd_object->setTextCursor(cursor_pos_col[pos], cursor_pos_row[pos]);
		lcd_object->printf("%s", data);
		lcd_object->setTextCursor(0, 0);
	}


};