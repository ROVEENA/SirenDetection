///////////////////////////////////////////////////////////
//  IdentifyEVImpl.cpp
//  Implementation of the Class IdentifyEVImpl
//  Created on:      18-Jan-2023 19:02:09
//  Original author: RLobo
///////////////////////////////////////////////////////////

#include "IdentifyEVImpl.h"

using adlux::vse::IdentifyEVImpl;





/**
 * Constructor. Actual port implementations are provided from the outside.
 * 
 * @param a_r_port_preprocessedsig_in
 * @param a_p_port_ev_out
 */
IdentifyEVImpl::IdentifyEVImpl(adlux::vse::IRPortPreprocessedSig& a_r_port_preprocessedsig_in, adlux::vse::IPPortEv& a_p_port_ev_out){}


/**
 * Destructor
 */
IdentifyEVImpl::~IdentifyEVImpl(){

}


/**
 * Initialize the component. 1. Initialize input ports 2. Initialize the
 * calculation 3. Initialize the output port
 */
void IdentifyEVImpl::Start(){
     r_port_preProcessed_sig_in.StartPort();
     calculator.start();
     p_port_ev_out.StartPort();
}


/**
 * Deinitializes the component: 1. Stop the output ports 2. Stop the calculation 3.
 * Stop the input ports
 */
void IdentifyEVImpl::Stop(){
     p_port_ev_out.StopPort();
     calculator.stop();
     r_port_preProcessed_sig_in.StopPort();
}


/**
 * Calculate vehicle state. 1. Read from input ports 2. Obtain output values from
 * the calculator 3. Write the output values to output ports
 */
void IdentifyEVImpl::Step(){
     //processedSig, ev_type 
    r_port_preProcessed_sig_in.CheckForPublishedUpdates(processedSig);
    EVVechicleType ev_type = calculator.identify(processedSig);
    p_port_ev_out.publishData(ev_type);
}