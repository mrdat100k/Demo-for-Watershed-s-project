class RelayController{

public:
	RelayController() state(false){

	}
	void ChangeState(){

	}

	bool GetState(){

	}

	void SetState(bool state){
		if (this->state != state){
			ChangeState();
		}
	}

private:
	bool state;

};