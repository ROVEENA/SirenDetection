///////////////////////////////////////////////////////////
//  VehicleModeCalculator.h
//  Implementation of the Class VehicleModeCalculator
//  Created on:      17-Jan-2023 19:01:18
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_C2F85A7C_524D_410a_9ABE_B0C1976C0AB5__INCLUDED_)
#define EA_C2F85A7C_524D_410a_9ABE_B0C1976C0AB5__INCLUDED_

#include "Mode.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 17-Jan-2023 19:01:18
		 */
		class VehicleModeCalculator
		{

		public:
			/**
			 * Default constructor
			 */
			VehicleModeCalculator();
			/**
			 * Default destructor
			 */
			virtual ~VehicleModeCalculator();
			/**
			 * Initializes the internal values
			 */
			void start();
			/**
			 * This function returns the current vehicle mode
			 */
			void get_mode();
			/**
			 * This function sets the vehicle mode
			 * 
			 * @param park_brake
			 */
			adlux::vse::VehicleMode set_mode(adlux::vse::ParkBrakeStatus park_brake);
			/**
			 * cleanup internal values
			 */
			void stop();

		private:
			adlux::vse::VehicleMode vehicle_mode;

		};

	}

}
#endif // !defined(EA_C2F85A7C_524D_410a_9ABE_B0C1976C0AB5__INCLUDED_)
