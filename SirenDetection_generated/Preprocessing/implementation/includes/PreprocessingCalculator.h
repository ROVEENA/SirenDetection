///////////////////////////////////////////////////////////
//  PreprocessingCalculator.h
//  Implementation of the Class PreprocessingCalculator
//  Created on:      18-Jan-2023 12:42:06
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_9E64414A_5543_4916_B51C_F01CC23ABB98__INCLUDED_)
#define EA_9E64414A_5543_4916_B51C_F01CC23ABB98__INCLUDED_

#include "PreProcessedSig.h"
#include "IRPortMicrophone.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 18-Jan-2023 12:42:06
		 */
		class PreprocessingCalculator
		{

		public:
			/**
			 * Default constructor
			 */
			PreprocessingCalculator();
			/**
			 * Default destructor
			 */
			virtual ~PreprocessingCalculator();
			/**
			 * Initializes the internal values
			 */
			void start();
			/**
			 * Performs preprocessing of the input
			 * 
			 * @param micInput
			 */
			adlux::vse::PreProcessedSig preprocess(adlux::vse::MicInput micInput);
			/**
			 * Cleanup internal values
			 */
			void stop();

		private:
			adlux::vse::PreProcessedSig preprocessed_sig;

		};

	}

}
#endif // !defined(EA_9E64414A_5543_4916_B51C_F01CC23ABB98__INCLUDED_)
