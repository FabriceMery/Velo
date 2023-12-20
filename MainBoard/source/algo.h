#ifndef ALGO_H
#define ALGO_H

#include "Globale.h"
#include "math.h"

#define RAD_TO_DEG (57.29578)
#define DEG_TO_RAD (0.01745329238)

// Distances between magnets and A3 sensor (used in position algorithm)

#define xC3_A1 (0.015573)		// Distance between A1 and C3 on C3 x axis (m)
#define yC3_A1 (0.004359)		// Distance between A1 and C3 on C3 y axis (m)
#define zC3_A1 (0.009450)		// Distance between A1 and C3 on C3 z axis (m)

#define xC3_A2 (0.016120)		// Distance between A2 and C3 on C3 x axis (m)
#define yC3_A2 (-0.003604)		// Distance between A2 and C3 on C3 y axis (m)
#define zC3_A2 (0.009450)		// Distance between A2 and C3 on C3 z axis (m)

#define xC3_A3 (0.00720) 		// Minimal distance between A3 and C3 on C3 x axis (m)
#define yC3_A3 (0)				// Minimal distance between A3 and C3 on C3 y axis (m), nominally set to zero

// Absolute distances between A1 and C2 or A2 and C1 in mm (used in angle algorithm)

#define Dx (0.00054)			// Distance between A1 and C2 or A2 and C1 on the counter x axis (m)
#define Dy (0.007963)			// Distance between A1 and C2 or A2 and C1 on the counter y axis (m)
#define Dz (0.002)			    // Distance between A1 and C2 or A2 and C1 on the counter z axis (m)

// Magnets dimensions and remanent magnetization

#define D_A1 (5)				// External diameter of A1 magnet (in mm)
#define H_A1 (1)				// Height of A1 magnet (in mm)
#define B_A1 (1.17) 			// Remanent magnetization of A1 magnet (in T)

#define D_A2 (5)				// External diameter of A2 magnet (in mm)
#define H_A2 (1)				// Height of A2 magnet (in mm)
#define B_A2 (1.17) 			// Remanent magnetization of A2 magnet (in T)

#define Dint_A3 (1)			    // Internal diameter of A3 magnet (in mm)
#define Dext_A3 (3)		    	// External diameter of A3 magnet (in mm)
#define H_A3 (2)		    	// Height of A3 magnet (in mm)
#define B_A3 (1.17)		    	// Remanent magnetization of A3 magnet (in T)

#define K_common param_flash.s_element.Param_mesure_volume.K_common
#define angle_2_offset param_flash.s_element.Param_mesure_volume.angle_2_offset
#define x_0_init param_flash.s_element.Param_mesure_volume.x_0_init
#define x_0_offset param_flash.s_element.Param_mesure_volume.x_0_offset

#define Ka_BxC3 param_flash.s_element.Param_mesure_position.Ka_BxC3
#define Kb_BxC3 param_flash.s_element.Param_mesure_position.Kb_BxC3
#define Ka_ByC3 param_flash.s_element.Param_mesure_position.Ka_ByC3
#define Kb_ByC3 param_flash.s_element.Param_mesure_position.Kb_ByC3
#define Ka_BzC3 param_flash.s_element.Param_mesure_position.Ka_BzC3
#define Kb_BzC3 param_flash.s_element.Param_mesure_position.Kb_BzC3

#define m_prime_A1  m_prime_coefficient(0, D_A1, H_A1, B_A1)
#define m_prime_A2  m_prime_coefficient(0, D_A2, H_A2, B_A2)
#define m_prime_A3  m_prime_coefficient(Dint_A3, Dext_A3, H_A3, B_A3)
#define PI  3.141592

#endif

