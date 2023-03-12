///////////////////////////////////////////////////////////
//  IPPortEv.h
//  Implementation of the Interface IPPortEv
//  Created on:      12-Jan-2023 16:33:21
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_B9A3CD4A_7432_4c5d_BCF0_A8FC0B6C3E94__INCLUDED_)
#define EA_B9A3CD4A_7432_4c5d_BCF0_A8FC0B6C3E94__INCLUDED_

#include "IfOutEV.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 12-Jan-2023 16:33:21
		 */
		class IPPortEv : public IdentifyEV::Interfaces::IfOutEV
		{

		public:
			IPPortEv() {

			}

			virtual ~IPPortEv() {

			}

		};

	}

}
#endif // !defined(EA_B9A3CD4A_7432_4c5d_BCF0_A8FC0B6C3E94__INCLUDED_)
