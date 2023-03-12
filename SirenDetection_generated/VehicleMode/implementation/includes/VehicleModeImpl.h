///////////////////////////////////////////////////////////
//  VehicleModeImpl.h
//  Implementation of the Class VehicleModeImpl
//  Created on:      17-Jan-2023 19:01:18
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_F21BEAC7_7D63_43c3_86B7_759303F541E1__INCLUDED_)
#define EA_F21BEAC7_7D63_43c3_86B7_759303F541E1__INCLUDED_

#include "IRPortECU.h"
#include "IPPortVehicleMode.h"
#include "VehicleModeCalculator.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * Implementation for the Vehicle Mode software component
		 * @author RLobo
		 * @version 1.0
		 * @updated 25-Jan-2023 13:02:07
		 */
		class VehicleModeImpl : public adlux::component_model::IComponentLifecycle
		{

		public:
			/**
			 * Constructor. Actual port implementations are provided from the outside.
			 * 
			 * @param a_r_port_ECU_in
			 * @param a_p_port_vehicle_mode_out
			 */
			VehicleModeImpl(adlux::vse::IRPortECU& a_r_port_ECU_in, adlux::vse::IPPortVehicleMode& a_p_port_vehicle_mode_out);
			/**
			 * Destructor
			 */
			virtual ~VehicleModeImpl();
			/**
			 * Initialize the component. 
			 * 1. Initialize input ports 
			 * 2. Initialize the calculation 
			 * 3. Initialize the output port
			 */
			virtual void Start();
			/**
			 * Deinitializes the component: 
			 * 1. Stop the output ports 
			 * 2. Stop the calculation 
			 * 3. Stop the input ports
			 */
			virtual void Stop();
			
			/**
			 * Calculate vehicle state. 
			 * 1. Read from input ports 
			 * 2. Obtain output values from the calculator 
			 * 3. Write the output values to output ports
			 */
			virtual void Step();
		private:
			adlux::vse::IRPortECU& r_port_ECU_in;
			adlux::vse::IPPortVehicleMode& p_port_vehicle_mode_out;
			adlux::vse::VehicleModeCalculator calculator;

		};

	}

}
#endif // !defined(EA_F21BEAC7_7D63_43c3_86B7_759303F541E1__INCLUDED_)
