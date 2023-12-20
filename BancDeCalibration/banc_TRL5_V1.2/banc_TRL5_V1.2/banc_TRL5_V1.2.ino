#include <BasicStepperDriver.h>
#include <QuadratureEncoder.h>

#define SERIAL_BAUDRATE				(115200)

// Pins role

#define STEPPER_PIN_MODE_0                (A0)
#define STEPPER_PIN_MODE_1                (A1)
#define STEPPER_PIN_MODE_2                (A2)

#define STEPPER_PIN_STEP                  (7)
#define STEPPER_PIN_DIR 			(6)

// Encoder and stepper motor properties

#define MOTOR_STEPS_PER_TURN			(200)
#define GEARBOX_RATIO				(60)
#define ENCODER_PULSES_PER_TURN		(4096)

#define MOTOR_MIN_SPEED_PRM			(1)
#define MOTOR_MAX_SPEED_RPM			(400)

// Default parameters

float motor_speed_rpm = 300; 				// Motor rotation speed in RPM (400 RPM max)
int number_of_microsteps = 32;			// More microsteps means less vibration and noise (1, 2, 4, 8, 16, 32 possible)

float encoder_angle = 0;
long motor_steps = 0;

String buffer_string("");
String read_string("");

Encoders Encoder(2,3);
BasicStepperDriver stepper(MOTOR_STEPS_PER_TURN, STEPPER_PIN_DIR, STEPPER_PIN_STEP);

void setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	Serial.setTimeout(10);

	pinMode(STEPPER_PIN_MODE_0, OUTPUT);
 	pinMode(STEPPER_PIN_MODE_1, OUTPUT);
 	pinMode(STEPPER_PIN_MODE_2, OUTPUT);
 	pinMode(STEPPER_PIN_DIR, OUTPUT); 
 	
  	microsteps(number_of_microsteps);
  	Encoder.setEncoderCount(0);
  	stepper.begin(motor_speed_rpm, number_of_microsteps);
}


void loop()
{
	if(Serial.available() > 0)
	{
		buffer_string.concat(Serial.readString()); // Complete the buffer with new data
		if(buffer_string.length() > 64) // Clear the buffer and send error if it contains too many characters
		{
			buffer_string.remove(0);
			Serial.println("eb"); // Buffer lenght error
		}
		int LF_index = buffer_string.indexOf('\n', 0); // Search the position of the next LF in the buffer
		while (LF_index > -1) // If a LF is found
		{
			read_string = buffer_string; // Copy the buffer
			buffer_string.remove(0, LF_index + 1); // Remove the part of the buffer that will be analyzed
			read_string.remove(LF_index); // Keep only the characters to be analyzed
			LF_index = buffer_string.indexOf('\n', 0); // Check the position of the next LF

			// Analyze of read_string

			if(read_string.length() < 11) // Any string should be shorter than 11 characters, this also allows to limit the maximal motor steps number
			{
				if (read_string.charAt(0) == 'r')
				{
					read_string.remove(0, 1);
					motor_steps = read_string.toInt();
					if (motor_steps != 0) // motor_steps = 0 means no integer was found
					{
						Serial.print('r');
						Serial.print(motor_steps);
						Serial.print("\n");
						stepper.move(-motor_steps);
						delay(10); // Delay to stabilize the encoder measurement
						encoder_angle = (float) Encoder.getEncoderCount() / (ENCODER_PULSES_PER_TURN * 4) * 360;
						Serial.print("ac");
						Serial.print(encoder_angle, 3);	
					}
					else
					{
						Serial.print("er"); // Error in a rotation command
					}	
				}
				
				else if (read_string.charAt(0) == 'c')
				{
					if(read_string.length() == 1)
					{
						encoder_angle = (float) Encoder.getEncoderCount() / (ENCODER_PULSES_PER_TURN * 4) * 360;
						Serial.print('c');
						Serial.print(encoder_angle, 3);	
					}
					else
					{
						Serial.print("ec"); // Error in an encoder command
					}
				}
				
				else if (read_string.charAt(0) == 's')
				{
					read_string.remove(0, 1);
					motor_speed_rpm = read_string.toInt(); // Return 0 if no integer is found
					if(motor_speed_rpm >= MOTOR_MIN_SPEED_PRM && motor_speed_rpm <= MOTOR_MAX_SPEED_RPM)
					{
						stepper.begin(motor_speed_rpm, number_of_microsteps);
						Serial.print('s');
						Serial.print(motor_speed_rpm, 0);
					}
					else
					{
						Serial.print("es"); // Error in a speed command
					}
				}
				
				else if (read_string.charAt(0) == 'm')
				{
					read_string.remove(0, 1);
					number_of_microsteps = read_string.toInt(); // Return 0 if no integer is found
					if (number_of_microsteps == 1 || number_of_microsteps == 2 || number_of_microsteps == 4 || number_of_microsteps == 8 || number_of_microsteps == 16 || number_of_microsteps == 32)
					{	
						microsteps(number_of_microsteps);
						stepper.begin(motor_speed_rpm, number_of_microsteps);
						Serial.print('m');		
						Serial.print(number_of_microsteps);
					}
					else
					{
						Serial.print("em"); // Error in a microstep command
					}
				}
				
				else if (read_string.charAt(0) == 'z')
				{
					if(read_string.length() == 1)
					{
						Encoder.setEncoderCount(0);
						encoder_angle = (float) Encoder.getEncoderCount() / (ENCODER_PULSES_PER_TURN * 4) * 360;
						Serial.print('z');
						Serial.print(encoder_angle, 3);						
					}
					else
					{
						Serial.print("ez"); // Error in a zero command
					}
				}
				
				else
				{
					Serial.print("en"); // 	Error in command name
				}
				
			}
			else
			{
				Serial.print("el"); // Error in string lenght
			}
			Serial.print("\n");
		}
	}	
}
