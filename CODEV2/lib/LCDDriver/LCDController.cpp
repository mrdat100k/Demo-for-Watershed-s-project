
#include "LCDController.h"


void LCDController::showLogo(uint8_t* watershed_logo_data){
		lcd_object.drawBitmap(0, 6, watershed_logo_data, 128, 48, WHITE);
		lcd_object.setTextCursor(0, 0);
		lcd_object.display();
	}
void LCDController::setPVVolt(float value){
		pv_volt = value;
	}

void LCDController::setPVCurr(float value){
		pv_curr = value;
	}

void LCDController::setPVPower(float value){
		pv_power = value;
	}

void LCDController::setPVEnergy(float value){
		pv_energy = value;
	}

void LCDController::setBattVolt(float value){
		battery_volt = value;
	}

void LCDController::setBattCurr(float value){
		battery_curr = value;
	}

void LCDController::setBattPower(float value){
		battery_power = value;
	}

void LCDController::setBattEnergy(float value){
		battery_energy = value;
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
					  writeAtPosition(0, "Main Menu:");
					  writeAtPosition(1, "Charge");
					  writeAtPosition(4, "Battery");
					  writeAtPosition(7, "AC On");
					  writeAtPosition(2, "Yes/No");
					  writeAtPosition(3, "DC/AC");
					  sprintf(buff, "%2.1f V ", battery_volt);
					  writeAtPosition(5, buff);
					  
					  //TODO: viet not
					  break;
		}
		case(1) : {
					  writeAtPosition(0, "PV Charge Info");
					  writeAtPosition(1, "PV Voltage");
					  writeAtPosition(4, "PV Current");
					  writeAtPosition(7, "PV Power");
					  writeAtPosition(10, "Energy");
					  sprintf(buff, "%2.1f mA ", pv_volt);
					  writeAtPosition(2, buff); 
					  sprintf(buff, "%2.1f mA ", pv_curr);
					  writeAtPosition(5, buff);
					  sprintf(buff, "%2.1f mA ", pv_power);
					  writeAtPosition(8, buff);
					  sprintf(buff, "%2.1f mA ", pv_energy);
					  writeAtPosition(11, buff);
					  if(state)
					  {
					    writeAtPosition(9, "Timer ON");
					  }
					  esle
					  {
						writeAtPosition(9, "Timer OFF");  
					  }
			
			
						
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
					  sprintf(buff, "%02d:%02d:%02d", hour, minute, second);
					  writeAtPosition(12, buff);
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

void LCDController::setTimer){
		this->hour = hour;
		this->minute = minute;
		this->second = second;
		this->state = state;
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
void LCDController::writeAtPosition(int pos, const char* data)
	{
		char col;
		char row;
		col = (pos-1)%3;
		row = (pos-1)/3;
		lcd_object->setTextCursor(cursor_pos_col[col], cursor_pos_row[row]);
		lcd_object->printf("%s", data);
		lcd_object->setTextCursor(0, 0);
	}


};
