///////////////////////////////////////////////////////////
//  PreprocessingImpl.cpp
//  Implementation of the Class PreprocessingImpl
//  Created on:      18-Jan-2023 12:54:01
//  Original author: RLobo
///////////////////////////////////////////////////////////

#include "PreprocessingImpl.h"

using adlux::vse::PreprocessingImpl;

/**
 * Destructor
 */
PreprocessingImpl::~PreProcessingImpl(){}


/**
 * Constructor. Actual port implementations are provided from the outside.
 * 
 * @param a_r_port_Mic_in
 * @param a_p_port_preprocessedSig_out
 */
PreprocessingImpl::PreprocessingImpl(adlux::vse::IRPortMicrophone& a_r_port_Mic_in, adlux::vse::IPPortPreProcessedSig& a_p_port_preprocessedSig_out)
                                     {}


/**
 * Initialize the component. 1. Initialize input ports 2. Initialize the
 * calculation 3. Initialize the output port
 */
void PreprocessingImpl::Start(){
     r_port_Mic_in.StartPort();
     calculator.start();
     p_port_preprocessedSig_out.StartPort();
}


/**
 * Calculate vehicle state. 1. Read from input ports 2. Obtain output values from
 * the calculator 3. Write the output values to output ports
 */
void PreprocessingImpl::Step(){
     //micIn , processedSig 
    r_port_Mic_in.CheckForPublishedUpdates(micIn);
    PreProcessedSig processedSig = calculator.preprocess(micIn);
    p_port_preprocessedSig_out.publishData(processedSig);
}


/**
 * Deinitializes the component: 1. Stop the output ports 2. Stop the calculation 3.
 * Stop the input ports
 */
void PreprocessingImpl::Stop(){
     p_port_preprocessedSig_out.StopPort();
     calculator.stop();
     r_port_Mic_in.StopPort();
}




