
#include "algo.h"

void read_angle1(float *angle); // Déclaration des prototypes des fonctions
void read_angle2(float *angle);
void read_mag_xyz(float *mag_x,float *mag_y,float *mag_z);
void algoVolume(VOLUME *v);
void algoPosition(POSITION *d);
float m_prime_coefficient(float Dint, float Dext, float H, float B);
static float number_of_turns_V2_2(float angle_1, float angle_2);
static float confidence_index_V2(float angle_1, float angle_2);
static float relative_angular_distance(float angle_1, float angle_2);
static float angle_offset(float angle, float offset);
static float turns_offset(float turns, float offset);
static float coordinates_to_angle(float x, float y);
static float magnetic_compensation_A2onC1_V1_9(float angle_1, float angle_2);
static float magnetic_compensation_A1onC2_V1_9(float angle_1, float angle_2);
static void magnetic_field_from_A1_on_C3(float *BxC3_A1, float *ByC3_A1, float *BzC3_A1, float angle_1_comp);
static void magnetic_field_from_A2_on_C3(float *BxC3_A2, float *ByC3_A2, float *BzC3_A2, float angle_2_comp);
static float magnetic_field_angle(float Bx, float Bz);
static float magnet_angle_to_position(float angle);



void algoVolume(VOLUME *v) 
{
	float angle_1;
	float angle_2;

	read_angle1(&angle_1); // Read the raw data from the angle sensors
	read_angle2(&angle_2);

	float angle_1_comp = magnetic_compensation_A2onC1_V1_9(angle_1, angle_2); // Magnetic compensation on both sensors
	float angle_2_comp = magnetic_compensation_A1onC2_V1_9(angle_1, angle_2);

	float angle_2_prime = angle_offset(angle_2_comp, angle_2_offset); // Offset on angle_2 to match the theoretical model

	float x_0 = number_of_turns_V2_2(angle_1_comp, angle_2_prime); // Algorithm to find the most likely number of turns
	float confidence_index = confidence_index_V2(angle_1_comp, angle_2_prime); // Calcul of the confidence index between 0 on 100

	float x_0_prime = turns_offset(x_0, -x_0_init); // First offset on the number of turns to match the calibration configuration
	float x_0_second = turns_offset(x_0_prime, -x_0_offset / 360); // Second offset to center the error from the calibration configuration, this is the result of the algorithm

	v->result.number_of_turns = x_0_second;
	v->result.confidence_index = confidence_index;
	v->result.angle_1_comp = angle_1_comp;
	v->result.angle_2_comp = angle_2_comp;
}



void algoPosition(POSITION *d)
{
	float angle_1;
	float angle_2;

	read_angle1(&angle_1); // Read the raw data from the angle sensors
	read_angle2(&angle_2);

	float angle_1_comp = magnetic_compensation_A2onC1_V1_9(angle_1, angle_2); // Magnetic compensation on both angle sensors to increase the angle accuracy
	float angle_2_comp = magnetic_compensation_A1onC2_V1_9(angle_1, angle_2);

	float BxC3;
	float ByC3;
	float BzC3;

	read_mag_xyz(&BxC3,&ByC3,&ByC3); // Read the raw data from the magnetometer

	float BxC3_A1 = 0; // Magnetic field from A1 on C3 x axis
	float ByC3_A1 = 0; // Magnetic field from A1 on C3 y axis
	float BzC3_A1 = 0; // Magnetic field from A1 on C3 z axis

	float BxC3_A2 = 0; // Magnetic field from A2 on C3 x axis
	float ByC3_A2 = 0; // Magnetic field from A2 on C3 y axis
	float BzC3_A2 = 0; // Magnetic field from A2 on C3 z axis

	magnetic_field_from_A1_on_C3(&BxC3_A1, &ByC3_A1, &BzC3_A1, angle_1_comp); // Calculate the magnetic field from of A1 on C3 knowing A1 angle
	magnetic_field_from_A2_on_C3(&BxC3_A2, &ByC3_A2, &BzC3_A2, angle_2_comp); // Calculate the magnetic field from of A2 on C3 knowing A2 angle
		
	float BxC3_parasitic = (BxC3_A1 + BxC3_A2) * Ka_BxC3 + Kb_BxC3; // Calculate the parasisitc effet of both A1 and A2 on each axis of C3 with linar calibration coefficients
	float ByC3_parasitic = (ByC3_A1 + ByC3_A2) * Ka_ByC3 + Kb_ByC3;
	float BzC3_parasitic = (BzC3_A1 + BzC3_A2) * Ka_BzC3 + Kb_BzC3;

	float BxC3_comp = BxC3 - BxC3_parasitic; // Calculate the magnetic field on the three axes after the compensation
	float ByC3_comp = ByC3 - ByC3_parasitic;
	float BzC3_comp = BzC3 - BzC3_parasitic;

	float A3_apparent_angle = magnetic_field_angle(BxC3_comp, BzC3_comp); // Calculate the angle of the magnetic field
	float A3_estimated_position = magnet_angle_to_position(A3_apparent_angle); // Convect the angle into a position, this is the result of the algoirthm

	d->result.position = A3_estimated_position;
	d->result.angle = A3_apparent_angle;
	d->result.BxC3_parasitic = BxC3_parasitic;
	d->result.ByC3_parasitic = ByC3_parasitic;
	d->result.BzC3_parasitic = BzC3_parasitic;
	d->result.BxC3_comp = BxC3_comp;
	d->result.ByC3_comp = ByC3_comp;
	d->result.BzC3_comp = BzC3_comp;
}



float m_prime_coefficient(float Dint, float Dext, float H, float B) // Calculate the global magnetic coefficient of a cylindrical magnet
{
	float volume = PI/4 * (pow(Dext * 0.001, 2) - pow(Dint * 0.001, 2)) * H * 0.001;	// Calculate the volume of the magnet in m^3
	float m_coefficient = B * volume / (4 * PI* 0.0000001); 					// Calculate the classical m_coefficient
	return (1000 * 4 * PI * 0.0000001 * m_coefficient / (4 * PI));			// Return the m_prime_coefficient
}



static float number_of_turns_V2_2(float angle_1, float angle_2)
{
	float positive_angle_difference;
	
	// Calculate the positive angle difference between angle_1 and angle_2
	if (angle_2 <= angle_1)
	{
		positive_angle_difference = angle_1 - angle_2;
	}
	else
	{
		positive_angle_difference = angle_1 - angle_2 + 360;
	}
	
	//Calculate the approximative R0 then R1 and R2 float turn numbers
	float R0_approximation = positive_angle_difference * 12 / 360;
	float R1_approximation = R0_approximation * 35 / 20;
	float R2_approximation = R0_approximation * 35 / 21;
	
	// angle_X_deduced is the value that angle_X should theoretically have if R0_approximation was the real R0 angle
	float angle_1_deduced = (R1_approximation - floor(R1_approximation)) * 360;
	float angle_2_deduced = (R2_approximation - floor(R2_approximation)) * 360; // Not used in further calculation
	
	// Relative angular distance between angle_1 (measured) and angle_1_deduced (from -180 to +180°), calculated only for angle_1 as results are always equal
	float difference_angle_1_measured_and_deduced = relative_angular_distance(angle_1, angle_1_deduced);
	
	// Find the number of the turns R0 linked to angle_1 (as in V1 of the algorithm) but also with angle_2
	float R0_from_angle_1 = R0_approximation - difference_angle_1_measured_and_deduced / 360 * 20 / 35;
	float R0_from_angle_2 = R0_approximation - difference_angle_1_measured_and_deduced / 360 * 21 / 35;
	
	// Use both R0_from_angle_1 and R0_from_angle_2 to find R0. The weights as linked to the theoretical angular resolution (slightly better for angle_1 than for angle_2)
	float weighted_average = (R0_from_angle_1 * 1.05 + R0_from_angle_2) / 2.05;

	// Convert results between 0 to 12 turns only (alpha_1)
	if (weighted_average < 0)
	{
		weighted_average = weighted_average + 12;
	}
	if (weighted_average >= 12)
	{
	  	weighted_average = weighted_average - 12;
	}

	return weighted_average;
}



static float confidence_index_V2(float angle_1, float angle_2)
{
	float positive_angle_difference;
	
	// Calculate the positive angle difference between angle_1 and angle_2
	if (angle_2 <= angle_1)
	{
		positive_angle_difference = angle_1 - angle_2;
	}
	else
	{
		positive_angle_difference = angle_1 - angle_2 + 360;
	}
	    
	// Calculate the approximative R1 float turn number
	float R1_approximation = positive_angle_difference * 12 / 360 * 35 / 20;

	// angle_X_deduced is the value that angle_X should theoretically have if R0_approximation was the real R0 angle
	float angle_1_deduced = (R1_approximation - floor(R1_approximation)) * 360;

	// Relative angular distance between angle_1 (measured) and angle_1_deduced (from -180 to +180°)
	float difference_angle_1_measured_and_deduced = relative_angular_distance(angle_1, angle_1_deduced);

	// Calculte the confidence index between 0% and 100%
	return 100 - fabs(difference_angle_1_measured_and_deduced) / 180 * 100;
}



static float relative_angular_distance(float angle_1, float angle_2) // 'Relative angular distance "angle_2 - angle_1" between two angles form 0° to 360°, the result is between -180 and +180°
{
	float result;

	if (angle_2 - angle_1 >= 0)
	{
		if (angle_2 - angle_1 <= 180)
		{
			result = angle_2 - angle_1; // Case 1
		}
		else
		{
			result = angle_2 - angle_1 - 360; // case 2
		}
	}
	else
	{
		if (angle_2 - angle_1 <= -180)
		{
			result = angle_2 - angle_1 + 360; // case 3
		}
		else
		{
			result = angle_2 - angle_1; // Case 4
		}
	}
 return result;
}



static float angle_offset(float angle, float offset)
{
	float result = angle + offset;

	if (result >= 360)
	{
		result = result - 360;
	}

	if (result < 0)
	{
		result = result + 360;
	}

	return result;
}



static float turns_offset(float turns, float offset)
{
	float result = turns + offset;

	if (result >= 12)
	{
		result = result - 12;
	}

	if (result < 0)
	{
		result = result + 12;
	}

	return result;
}



static float coordinates_to_angle(float x, float y)
{
	float atan2_result = RAD_TO_DEG * atan2(y, x);
	
	if (atan2_result < 0)
	{
		return atan2_result + 360;
	}
	else
	{
		return atan2_result;
	}
}



static float magnetic_compensation_A2onC1_V1_9(float angle_1, float angle_2)
{
	// Compensation of the effect of the magnet A2 on the sensor C1

	float angle_2_rad = DEG_TO_RAD * angle_2;

	//Parameters calculated from the input ones :

	float r = sqrt(pow(Dx, 2) + pow(Dy, 2) + pow(Dz, 2)); // Absolute distance r between the center of C1 and the center of A2 (m)
	float B_A2onC1_min = m_prime_A2 / pow(r, 3); // Minimal value that B_A2onC1 can have	

	// Distances between C1 and A2 in the basis of A2 (m) :

	float Dx_A2 = Dz; // Not useful for the function, can be removed for optimization
	float Dy_A2 = -Dx * cos(angle_2_rad) + Dy * sin(angle_2_rad);
	float Dz_A2 = -Dx * sin(angle_2_rad) - Dy * cos(angle_2_rad);

	// B_A2/C1' in the basis of A2 (mT) :
    
	float xB_A2onC1_prime = 3 * m_prime_A2 * Dx_A2 * Dy_A2 / pow(r, 5); // Not useful for the function, can be removed for optimization
	float yB_A2onC1_prime = 3 * m_prime_A2 * Dy_A2 * Dz_A2 / pow(r, 5);
	float zB_A2onC1_prime = m_prime_A2 * (3 * pow(Dz_A2, 2) - pow(r, 2)) / pow(r, 5);
	
	// B_A2/C1 in the basis of C1 (mT) :
            
	float xB_A2onC1 = -yB_A2onC1_prime * cos(angle_2_rad) - zB_A2onC1_prime * sin(angle_2_rad);
    float yB_A2onC1 = yB_A2onC1_prime * sin(angle_2_rad) - zB_A2onC1_prime * cos(angle_2_rad);
    float zB_A2onC1 = xB_A2onC1_prime; // Not useful for the function, can be removed for optimization

	// B_A2onC1 vector (modulus and angle) :
    float B_A2onC1 = hypot(xB_A2onC1, yB_A2onC1); // Modulus of the vector
    float angle_B_A2onC1 = coordinates_to_angle(-yB_A2onC1, -xB_A2onC1); // Angle of the vector
    
	float e_1 = relative_angular_distance(angle_1, angle_B_A2onC1); // Angular distance between angle_C1 and angle_B_A2onC1 :
	
	float delta_angle_B_C1 = RAD_TO_DEG * atan(K_common / 1000 * B_A2onC1 / B_A2onC1_min * sin( -DEG_TO_RAD * e_1)); // Angular variation calculated by the algorithm :
    
	// Return the result of the algorithm (angle_1_comp) :
    
	return angle_offset(angle_1, delta_angle_B_C1); 
}



static float magnetic_compensation_A1onC2_V1_9(float angle_1, float angle_2)
{
	// Compensation of the effect of the magnet A1 on the sensor C2

	float angle_1_rad = DEG_TO_RAD * angle_1;

	//Parameters calculated from the input ones :

	float r = sqrt(pow(Dx, 2) + pow(Dy, 2) + pow(Dz, 2)); // Absolute distance r between the center of C2 and the center of A1 (m)
	float B_A1onC2_min = m_prime_A1 / pow(r, 3); // Minimal value that B_A1onC2 can have	

	// Distances between C2 and A1 in the basis of A1 (m) :

	float Dx_A1 = Dz; // Not useful for the function, can be removed for optimization
	float Dy_A1 = Dx * cos(angle_1_rad) - Dy * sin(angle_1_rad);
	float Dz_A1 = Dx * sin(angle_1_rad) + Dy * cos(angle_1_rad);

	// B_A1/C2' in the basis of A1 (mT) :

	float xB_A1onC2_prime = 3 * m_prime_A1 * Dx_A1 * Dy_A1 / pow(r, 5); // Not useful for the function, can be removed for optimization
	float yB_A1onC2_prime = 3 * m_prime_A1 * Dy_A1 * Dz_A1 / pow(r, 5);
	float zB_A1onC2_prime = m_prime_A1 * (3 * pow(Dz_A1, 2) - pow(r, 2)) / pow(r, 5);
	
	// B_A1/C2 in the basis of C1 (mT) :
            
	float xB_A1onC2 = yB_A1onC2_prime * cos(angle_1_rad) + zB_A1onC2_prime * sin(angle_1_rad);
    float yB_A1onC2 = -yB_A1onC2_prime * sin(angle_1_rad) + zB_A1onC2_prime * cos(angle_1_rad);
    float zB_A1onC2 = xB_A1onC2_prime; // Not useful for the function, can be removed for optimization

	// B_A1onC2 vector (modulus and angle) :
	float B_A1onC2 = hypot(xB_A1onC2, yB_A1onC2); // Modulus of the vector
	float angle_B_A1onC2 = coordinates_to_angle(yB_A1onC2, xB_A1onC2); // Angle of the vector

	float e_2 = relative_angular_distance(angle_2, angle_B_A1onC2); // Angular distance between angle_C2 and angle_B_A1onC2 :

	float delta_angle_B_C2 = RAD_TO_DEG * atan(K_common / 1000 * B_A1onC2 / B_A1onC2_min * sin( -DEG_TO_RAD * e_2)); // Angular variation calculated by the algorithm :
	return angle_offset(angle_2, delta_angle_B_C2); // Return the result of the algorithm (angle_1_comp) :
}



static void magnetic_field_from_A1_on_C3(float *BxC3_A1, float *ByC3_A1, float *BzC3_A1, float angle_1_comp)
{
	float r_A1 = sqrt(pow(xC3_A1, 2) + pow(yC3_A1, 2) + pow(zC3_A1, 2)); // Radius between A1 and C3 in m

	// Distance between A1 and C3 in the reference of A1
	
	float xA1_C3 = zC3_A1;
	float yA1_C3 = -xC3_A1 * cos(DEG_TO_RAD * angle_1_comp) - yC3_A1 * sin(DEG_TO_RAD * angle_1_comp);
	float zA1_C3 = yC3_A1 * cos(DEG_TO_RAD * angle_1_comp) - xC3_A1 * sin(DEG_TO_RAD * angle_1_comp);

	// Magnetic field from A1 measured by C3 in the reference of A1

	float BxA1 = 3 * m_prime_A1 * xA1_C3 * zA1_C3 / pow(r_A1, 5);
	float ByA1 = 3 * m_prime_A1 * yA1_C3 * zA1_C3 / pow(r_A1, 5);
	float BzA1 = m_prime_A1 * ( 3 * pow(zA1_C3, 2) - pow(r_A1, 2)) / pow(r_A1, 5);

	// Magnetic field from A1 measured by C3 in the reference of C3 (in mT)

	*BxC3_A1 = 1000 * (ByA1 * cos(DEG_TO_RAD * angle_1_comp) + BzA1 * sin(DEG_TO_RAD * angle_1_comp));
	*ByC3_A1 = 1000 * (-BzA1 * cos(DEG_TO_RAD * angle_1_comp) + ByA1 * sin(DEG_TO_RAD * angle_1_comp));
	*BzC3_A1 = 1000 * (-BxA1);
}



static void magnetic_field_from_A2_on_C3(float *BxC3_A2, float *ByC3_A2, float *BzC3_A2, float angle_2_comp)
{
	float r_A2 = sqrt(pow(xC3_A2, 2) + pow(yC3_A2, 2) + pow(zC3_A2, 2)); // Radius between A2 and C3 in m

	// Distance between A2 and C3 in the reference of A1
	
	float xA2_C3 = zC3_A2;
	float yA2_C3 = xC3_A2 * cos(DEG_TO_RAD * angle_2_comp) + yC3_A2 * sin(DEG_TO_RAD * angle_2_comp);
	float zA2_C3 = -yC3_A2 * cos(DEG_TO_RAD * angle_2_comp) + xC3_A2 * sin(DEG_TO_RAD * angle_2_comp);

	// Magnetic field from A2 measured by C3 in the reference of A1

	float BxA2 = 3 * m_prime_A2 * xA2_C3 * zA2_C3 / pow(r_A2, 5);
	float ByA2 = 3 * m_prime_A2 * yA2_C3 * zA2_C3 / pow(r_A2, 5);
	float BzA2 = m_prime_A2 * ( 3 * pow(zA2_C3, 2) - pow(r_A2, 2)) / pow(r_A2, 5);

	// Magnetic field from A2 measured by C3 in the reference of C3 (in mT)

	*BxC3_A2 = 1000 * (-ByA2 * cos(DEG_TO_RAD * angle_2_comp) - BzA2 * sin(DEG_TO_RAD * angle_2_comp));
	*ByC3_A2 = 1000 * (BzA2 * cos(DEG_TO_RAD * angle_2_comp) - ByA2 * sin(DEG_TO_RAD * angle_2_comp));
	*BzC3_A2 = 1000 * (-BxA2);
}



static float magnetic_field_angle(float Bx, float Bz) // Calculate the mangetic field angle (in degrees) of a magnet sliding arount a magnetometer
{
	if (Bx == 0)
	{
		return 0;
	}
	else if (Bx > 0)
	{
		return RAD_TO_DEG * atan(Bz / Bx) + 90;
	}
	else
	{
		return RAD_TO_DEG * atan(Bz / Bx) - 90;
	}
}



static float magnet_angle_to_position(float angle) // Estimation of the magnet position in mm based on the magnetic field angle
{
	if (angle == 0)
	{
		return 0;
	}
	else if (angle < 0)
	{
		return 1000 * 1/4 * ( (3 * xC3_A3 * tan(DEG_TO_RAD * (angle + 90))) - xC3_A3 * sqrt(9 * pow(tan(DEG_TO_RAD * (angle + 90)), 2) + 8) );
	}
	else
	{
		return 1000 * 1/4 * ( (3 * xC3_A3 * tan(DEG_TO_RAD * (angle - 90))) + xC3_A3 * sqrt(9 * pow(tan(DEG_TO_RAD * (angle - 90)), 2) + 8) );
	}	
}

