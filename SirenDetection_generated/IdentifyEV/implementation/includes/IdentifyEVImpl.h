///////////////////////////////////////////////////////////
//  IdentifyEVImpl.h
//  Implementation of the Class IdentifyEVImpl
//  Created on:      18-Jan-2023 19:02:09
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_EAB77BC3_E98E_42b2_813B_C7DCC367E15A__INCLUDED_)
#define EA_EAB77BC3_E98E_42b2_813B_C7DCC367E15A__INCLUDED_

#include "IdentifyEvCalculator.h"
#include "IRPortPreprocessedSig.h"
#include "IPPortEv.h"
#include "IComponentLifecycle.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * Implementation for the IdentifyEV software component
		 * @author RLobo
		 * @version 1.0
		 * @updated 26-Jan-2023 23:04:52
		 */
		class IdentifyEVImpl : public adlux::component_model::IComponentLifecycle
		{

		public:

			/**
			 * Constructor. Actual port implementations are provided from the outside.
			 * 
			 * @param a_r_port_preprocessedsig_in
			 * @param a_p_port_ev_out
			 */
			IdentifyEVImpl(adlux::vse::IRPortPreprocessedSig& a_r_port_preprocessedsig_in, adlux::vse::IPPortEv& a_p_port_ev_out);
			/**
			 * Destructor
			 */
			virtual ~IdentifyEVImpl();
			/**
			 * Initialize the component. 1. Initialize input ports 2. Initialize the
			 * calculation 3. Initialize the output port
			 */
			virtual void Start();
			/**
			 * Deinitializes the component: 1. Stop the output ports 2. Stop the calculation 3.
			 * Stop the input ports
			 */
			virtual void Stop();
			/**
			 * Calculate vehicle state. 1. Read from input ports 2. Obtain output values from
			 * the calculator 3. Write the output values to output ports
			 */
			virtual void Step();

		private:
			adlux::vse::IRPortPreprocessedSig& r_port_preProcessed_sig_in;
			adlux::vse::IPPortEv& p_port_ev_out;
			adlux::vse::IdentifyEvCalculator calculator;

		};

	}

}
#endif // !defined(EA_EAB77BC3_E98E_42b2_813B_C7DCC367E15A__INCLUDED_)
