
void microsteps(int number_of_microsteps)
{
	switch(number_of_microsteps)
	{
		case 1:
			digitalWrite(STEPPER_PIN_MODE_0, 0);
    			digitalWrite(STEPPER_PIN_MODE_1, 0);
    			digitalWrite(STEPPER_PIN_MODE_2, 0);
    			break;
    		case 2:
    		   	digitalWrite(STEPPER_PIN_MODE_0, 1);
    			digitalWrite(STEPPER_PIN_MODE_1, 0);
    			digitalWrite(STEPPER_PIN_MODE_2, 0);
    			break;
    		case 4:
    			digitalWrite(STEPPER_PIN_MODE_0, 0);
    			digitalWrite(STEPPER_PIN_MODE_1, 1);
    			digitalWrite(STEPPER_PIN_MODE_2, 0);
    			break;
    		case 8:
    			digitalWrite(STEPPER_PIN_MODE_0, 1);
    			digitalWrite(STEPPER_PIN_MODE_1, 1);
    			digitalWrite(STEPPER_PIN_MODE_2, 0);
    			break;
    		case 16:
    		      digitalWrite(STEPPER_PIN_MODE_0, 0);
    			digitalWrite(STEPPER_PIN_MODE_1, 0);
    			digitalWrite(STEPPER_PIN_MODE_2, 1);
    			break;
    		case 32:
    		      digitalWrite(STEPPER_PIN_MODE_0, 1);
    			digitalWrite(STEPPER_PIN_MODE_1, 0);
    			digitalWrite(STEPPER_PIN_MODE_2, 1);
    			break;
	}
}
