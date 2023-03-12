///////////////////////////////////////////////////////////
//  AlertDecisionImpl.h
//  Implementation of the Class AlertDecisionImpl
//  Created on:      12-Jan-2023 18:43:02
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_84DE5F64_D581_4d26_A819_C4C8976070CB__INCLUDED_)
#define EA_84DE5F64_D581_4d26_A819_C4C8976070CB__INCLUDED_

#include "IRPortVehicleMode.h"
#include "IRPortEvVechicle.h"
#include "AlertDecisionCalculator.h"
#include "IPPortShowAlert.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * Implementation for the AlertDecision software component
		 * @author RLobo
		 * @version 1.0
		 * @updated 25-Jan-2023 16:25:44
		 */
		class AlertDecisionImpl : public adlux::component_model::IComponentLifecycle
		{

		public:

			/**
			 * Constructor. Actual port implementations are provided from the outside.
			 * 
			 * @param a_r_port_vehicle_mode_in
			 * @param a_r_port_ev_type
			 * @param a_p_port_alertState
			 */
			AlertDecisionImpl(adlux::vse::IRPortVehicleMode& a_r_port_vehicle_mode_in, 
							  adlux::vse::IRPortEvVechicle& a_r_port_ev_type, 
							  adlux::vse::IPPortShowAlert& a_p_port_alertState);
			/**
			 * Destructor
			 */
			virtual ~AlertDecisionImpl();
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
			adlux::vse::IRPortVehicleMode& r_port_vehicle_mode_out;
			adlux::vse::IRPortEvVechicle& r_port_ev_type;
			adlux::vse::IPPortShowAlert& p_port_alertState;
			adlux::vse::AlertDecisionCalculator calculator;

		};

	}

}
#endif // !defined(EA_84DE5F64_D581_4d26_A819_C4C8976070CB__INCLUDED_)
