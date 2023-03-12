///////////////////////////////////////////////////////////
//  IdentifyEvCalculator.h
//  Implementation of the Class IdentifyEvCalculator
//  Created on:      18-Jan-2023 18:52:39
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_AC1C1DDF_DD2A_4860_843A_708B23636169__INCLUDED_)
#define EA_AC1C1DDF_DD2A_4860_843A_708B23636169__INCLUDED_

#include "EVVehicleType.h"
#include "PreProcessedSig.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 18-Jan-2023 18:52:39
		 */
		class IdentifyEvCalculator
		{

		public:
			/**
			 * Default constructor
			 */
			IdentifyEvCalculator();
			/**
			 * Default destructor
			 */
			virtual void ~IdentifyEvCalculator();
			/**
			 * Initializes the internal values
			 */
			void start();
			/**
			 * cleanup internal values
			 */
			void stop();
			/**
			 * 
			 * @param preprocessedSig
			 */
			adlux::vse::EVVehicleType identify(adlux::vse::PreProcessedSig preprocessedSig);

		private:
			adlux::vse::EVVehicleType ev_type;

		};

	}

}
#endif // !defined(EA_AC1C1DDF_DD2A_4860_843A_708B23636169__INCLUDED_)
