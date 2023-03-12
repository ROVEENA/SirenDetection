///////////////////////////////////////////////////////////
//  AlertDecisionCalculator.h
//  Implementation of the Class AlertDecisionCalculator
//  Created on:      25-Jan-2023 16:22:17
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_02829071_03AE_48e7_B6F0_08FA7679D498__INCLUDED_)
#define EA_02829071_03AE_48e7_B6F0_08FA7679D498__INCLUDED_

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 25-Jan-2023 16:22:17
		 */
		class AlertDecisionCalculator
		{

		public:
			/**
			 * Default constructor
			 */
			AlertDecisionCalculator();
			/**
			 * Default destructor
			 */
			virtual ~AlertDecisionCalculator();
			/**
			 * Initializes the internal values
			 */
			void start();
			/**
			 * This function gives the final decision
			 * 
			 * @param ev_type
			 * @param vehicleMode
			 */
			adlux::vse::AlertState showAlert(adlux::vse::EVVehicleType ev_type, adlux::vse::VehicleMode vehicleMode);
			/**
			 * cleanup internal values
			 */
			void stop();

		private:
			adlux::vse::AlertState alert;

		};

	}

}
#endif // !defined(EA_02829071_03AE_48e7_B6F0_08FA7679D498__INCLUDED_)
