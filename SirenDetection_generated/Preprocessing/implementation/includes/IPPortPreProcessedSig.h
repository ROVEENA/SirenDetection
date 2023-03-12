///////////////////////////////////////////////////////////
//  IPPortPreProcessedSig.h
//  Implementation of the Interface IPPortPreProcessedSig
//  Created on:      18-Jan-2023 12:21:55
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_DC2F5B15_19F0_4a81_93D9_B4224D80DA26__INCLUDED_)
#define EA_DC2F5B15_19F0_4a81_93D9_B4224D80DA26__INCLUDED_

#include "IfOutPreprocessedSig.h"
#include "IPortLifeycle.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 18-Jan-2023 12:21:55
		 */
		class IPPortPreProcessedSig : public adlux::vse::IfOutPreprocessedSig, public adlux::component_model::IPortLifeycle
		{


		};

	}

}
#endif // !defined(EA_DC2F5B15_19F0_4a81_93D9_B4224D80DA26__INCLUDED_)
