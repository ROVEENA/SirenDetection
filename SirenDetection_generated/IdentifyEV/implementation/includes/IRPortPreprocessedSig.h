///////////////////////////////////////////////////////////
//  IRPortPreprocessedSig.h
//  Implementation of the Interface IRPortPreprocessedSig
//  Created on:      12-Jan-2023 16:33:21
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_26A1BB90_6BFC_4381_9483_F3DFD980CD32__INCLUDED_)
#define EA_26A1BB90_6BFC_4381_9483_F3DFD980CD32__INCLUDED_

#include "IfInPreProcessedSignal.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 12-Jan-2023 16:33:21
		 */
		class IRPortPreprocessedSig : public IdentifyEV::Interfaces::IfInPreProcessedSignal
		{

		public:
			IRPortPreprocessedSig() {

			}

			virtual ~IRPortPreprocessedSig() {

			}

		};

	}

}
#endif // !defined(EA_26A1BB90_6BFC_4381_9483_F3DFD980CD32__INCLUDED_)
