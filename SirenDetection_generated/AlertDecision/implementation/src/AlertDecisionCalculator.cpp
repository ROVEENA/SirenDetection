///////////////////////////////////////////////////////////
//  AlertDecisionCalculator.cpp
//  Implementation of the Class AlertDecisionCalculator
//  Created on:      25-Jan-2023 16:22:17
//  Original author: RLobo
///////////////////////////////////////////////////////////

#include "AlertDecisionCalculator.h"

using adlux::vse::AlertDecisionCalculator;




/**
 * Default constructor
 */
AlertDecisionCalculator::AlertDecisionCalculator(){

}


/**
 * Default destructor
 */
AlertDecisionCalculator::~AlertDecisionCalculator(){

}


/**
 * Initializes the internal values
 */
void AlertDecisionCalculator::start(){

}


/**
 * This function gives the final decision
 * 
 * @param ev_type
 * @param vehicleMode
 */
adlux::vse::AlertState AlertDecisionCalculator::showAlert(adlux::vse::EVVehicleType ev_type, adlux::vse::VehicleMode vehicleMode){

   if((vehicleMode == DRIVE ) && (ev_type != 0))
   {
	 alert = ON ; 
   }
	return  alert;
}


/**
 * cleanup internal values
 */
void AlertDecisionCalculator::stop(){

}