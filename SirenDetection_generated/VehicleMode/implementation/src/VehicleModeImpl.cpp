///////////////////////////////////////////////////////////
//  VehicleModeImpl.cpp
//  Implementation of the Class VehicleModeImpl
//  Created on:      17-Jan-2023 19:02:15
//  Original author: RLobo
///////////////////////////////////////////////////////////

#include "VehicleModeImpl.h"

using adlux::vse::VehicleModeImpl;

namespace adlux {
namespace vse {


/**
 * Constructor. Actual port implementations are provided from the outside.
 * 
 * @param a_r_port_ECU_in
 * @param a_p_port_vehicle_mode_out
 */
VehicleModeImpl::VehicleModeImpl(adlux::vse::IRPortECU& a_r_port_ECU_in, adlux::vse::IPPortVehicleMode& a_p_port_vehicle_mode_out){}


/**
 * Destructor
 */
VehicleModeImpl::~VehicleModeImpl(){}

/**
 * Initialize the component. 1. Initialize input ports 2. Initialize the
 * calculation 3. Initialize the output port
 */
void VehicleModeImpl::Start(){
     r_port_ECU_in.StartPort();
     calculator.start();
     p_port_vehicle_mode_out.StartPort();
}

/**
 * Deinitializes the component: 1. Stop the output ports 2. Stop the calculation 3.
 * Stop the input ports
 */
void VehicleModeImpl::Stop(){
     p_port_vehicle_mode_out.StopPort();
     calculator.stop();
     r_port_ECU_in.StopPort();

}

/**
 * Calculate vehicle state. 1. Read from input ports 2. Obtain output values from
 * the calculator 3. Write the output values to output ports
 */
void VehicleModeImpl::Step(){
    // ParkBrakeStatus park_brake need to initialiye here
    r_port_ECU_in.CheckForPublishedUpdates(park_brake);

    VehicleMode vehicleMode = calculator.set_mode(park_brake);
    
    p_port_vehicle_mode_out.publishData(vehicleMode);
}
}
}