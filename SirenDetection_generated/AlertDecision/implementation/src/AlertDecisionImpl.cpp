///////////////////////////////////////////////////////////
//  AlertDecisionImpl.cpp
//  Implementation of the Class AlertDecisionImpl
//  Created on:      12-Jan-2023 18:43:02
//  Original author: RLobo
///////////////////////////////////////////////////////////

#include "AlertDecisionImpl.h"

using adlux::vse::AlertDecisionImpl;


namespace adlux {
namespace vse {

/**
 * Constructor. Actual port implementations are provided from the outside.
 * 
 * @param a_r_port_vehicle_mode_in
 * @param a_r_port_ev_type
 * @param a_p_port_alertState
 */
AlertDecisionImpl::AlertDecisionImpl(adlux::vse::IRPortVehicleMode& a_r_port_vehicle_mode_in, adlux::vse::IRPortEvVechicle& a_r_port_ev_type, adlux::vse::IPPortShowAlert& a_p_port_alertState){}


/**
 * Destructor
 */
AlertDecisionImpl::~AlertDecisionImpl(){}


/**
 * Initialize the component. 1. Initialize input ports 2. Initialize the
 * calculation 3. Initialize the output port
 */
void AlertDecisionImpl::Start(){

	//This function initialises 
     r_port_vehicle_mode_out.StartPort();
	 r_port_ev_type.StartPort();
     calculator.start();
     p_port_alertState.StartPort();
}


/**
 * Deinitializes the component: 1. Stop the output ports 2. Stop the calculation 3.
 * Stop the input ports
 */
void AlertDecisionImpl::Stop(){
     p_port_alertState.StopPort();
     calculator.stop();
	 r_port_ev_type.StopPort();
     r_port_vehicle_mode_out.StopPort();
}


/**
 * Calculate vehicle state. 1. Read from input ports 2. Obtain output values from
 * the calculator 3. Write the output values to output ports
 */
void AlertDecisionImpl::Step(){
    // vehicelMode ,  ev_type need to initialize
    r_port_vehicle_mode_out.CheckForPublishedUpdates(vehicelMode);
	r_port_ev_type.CheckForPublishedUpdates(ev_type);
    AlertSate alert_state = calculator.showAlert(ev_type,vehicelMode);
    p_port_alertState.publishData(alert_state);
}

}
}