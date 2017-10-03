#ifndef _INAREADER_HPP_
#define _INAREADER_HPP_
#include "INA219.hpp"
class INAReader{
public:
	//************************************
	// Method:    INAReader::INAReader
	// Description:  INAReader constructor
	// Access:    public
	// Returns:
	// Qualifier:
	//************************************
	INAReader(PinName sda, PinName scl, int bat_addr=0x40, int pv_addr=0x41)
	{
		INA_batmeasure_object = new INA219(sda, scl, bat_addr);
		INA_pvmeasure_object = new INA219(sda, scl, pv_addr);
	}
	void Calibration();
	void Scan();
	float getBattVolt();
	float getBattCurr();
	float getBattPower();
	float getPVVolt();
	float getPVCurr();
	float getPVPower();
private:
	INA219* INA_batmeasure_object;
	INA219* INA_pvmeasure_object;
	float pv_volt;
	float pv_curr;
	float pv_power;
	float battery_volt;
	float battery_curr;
	float battery_power;
};
void INAReader::Calibration()
    {
	      INA_batmeasure_object -> calibrate_32v_3200mA();
		    INA_pvmeasure_object -> calibrate_32v_3200mA();
    }
void INAReader::Scan()
    {
		pv_volt = INA_pvmeasure_object -> read_bus_voltage();
		pv_curr = INA_pvmeasure_object -> read_current_mA();
		pv_power = INA_pvmeasure_object -> read_power_mW();
		battery_volt = INA_batmeasure_object -> read_bus_voltage();
		battery_curr = INA_batmeasure_object -> read_current_mA();
		battery_power = INA_batmeasure_object -> read_power_mW();
	}
float INAReader::getBattVolt()
    {
		return battery_volt;
	}
float INAReader::getBattCurr()
    {
		return battery_curr;
	}
float INAReader::getBattPower()
    {
		return battery_power;
	}
float INAReader::getPVVolt()
    {
		return pv_volt;
	}
float INAReader::getPVCurr()
    {
		return pv_curr;
	}
float INAReader::getPVPower()
    {
		return pv_power;
	}
	#endif /*_INAREADER_HPP_*/
