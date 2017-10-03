#ifndef _RELAY_H_
#define _RELAY_H_
#include <mbed.h>
#include "IOPins.h"
class RelayController{

public:
	RelayController(): state(false){
		relay = new DigitalOut(INVERTER_ENABLE_PIN);
	}
	void ChangeState(){
		state = !state;
		relay->write(state);

	}

	bool GetState(){
		return state;
	}

	void SetState(bool state){

		relay->write(state);
		this->state = state;
	}

private:
	bool state;
	DigitalOut* relay;


};
#endif /*_RELAY_H_*/
