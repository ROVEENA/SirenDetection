///////////////////////////////////////////////////////////
//  VehicleModeCalculator.cpp
//  Implementation of the Class VehicleModeCalculator
//  Created on:      17-Jan-2023 19:02:15
//  Original author: RLobo
///////////////////////////////////////////////////////////

#include "VehicleModeCalculator.h"

using adlux::vse::VehicleModeCalculator;




/**
 * Default constructor
 */
VehicleModeCalculator::VehicleModeCalculator(){

}


/**
 * Default destructor
 */
VehicleModeCalculator::~VehicleModeCalculator(){

}


/**
 * Initializes the internal values
 */
void VehicleModeCalculator::start(){

}


/**
 * This function returns the current vehicle mode
 */
void VehicleModeCalculator::get_mode(){

	return vehicle_mode;
}


/**
 * This function sets the vehicle mode
 * 
 * @param park_brake
 */
adlux::vse::VehicleMode VehicleModeCalculator::set_mode(adlux::vse::ParkBrakeStatus park_brake){

	if(parkbrakestatus == false)
	{ 
	    vehicle_mode = DRIVE;
	}
	else{
	    vehicle_mode = PARK;
	}
	return vehicle_mode;
}


/**
 * cleanup internal values
 */
void VehicleModeCalculator::stop(){

}