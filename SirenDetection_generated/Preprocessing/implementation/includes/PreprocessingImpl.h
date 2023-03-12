///////////////////////////////////////////////////////////
//  PreprocessingImpl.h
//  Implementation of the Class PreprocessingImpl
//  Created on:      18-Jan-2023 12:54:01
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_15225C80_15CA_40f1_85F6_29770EA2DDBC__INCLUDED_)
#define EA_15225C80_15CA_40f1_85F6_29770EA2DDBC__INCLUDED_

#include "PreprocessingCalculator.h"
#include "IComponentLifecycle.h"
#include "IRPortMicrophone.h"
#include "IPPortPreProcessedSig.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * Implementation for the Preprocessing software component
		 * @author RLobo
		 * @version 1.0
		 * @updated 26-Jan-2023 20:33:20
		 */
		class PreprocessingImpl : public adlux::component_model::IComponentLifecycle
		{

		public:
			/**
			 * Destructor
			 */
			virtual ~PreProcessingImpl();

			/**
			 * Constructor. Actual port implementations are provided from the outside.
			 * 
			 * @param a_r_port_Mic_in
			 * @param a_p_port_preprocessedSig_out
			 */
			PreprocessingImpl(adlux::vse::IRPortMicrophone& a_r_port_Mic_in, adlux::vse::IPPortPreProcessedSig& a_p_port_preprocessedSig_out);
			/**
			 * Initialize the component. 1. Initialize input ports 2. Initialize the
			 * calculation 3. Initialize the output port
			 */
			virtual void Start();
			/**
			 * Calculate vehicle state. 1. Read from input ports 2. Obtain output values from
			 * the calculator 3. Write the output values to output ports
			 */
			virtual void Step();
			/**
			 * Deinitializes the component: 1. Stop the output ports 2. Stop the calculation 3.
			 * Stop the input ports
			 */
			virtual void Stop();
		private:
			adlux::vse::IRPortMicrophone& r_port_Mic_in;
			adlux::vse::IPPortPreProcessedSig& p_port_preprocessedSig_out;
			adlux::vse::IdentifyEvCalculator calculator;

		};

	}

}
#endif // !defined(EA_15225C80_15CA_40f1_85F6_29770EA2DDBC__INCLUDED_)
