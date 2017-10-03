class RelayController{

public:
	RelayController() state(false){
		relay = new DigitalOut(INVERTER_ENABLE_PIN);
	}
	void ChangeState(){
		state = !state;
		relay->write(!state);
		
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