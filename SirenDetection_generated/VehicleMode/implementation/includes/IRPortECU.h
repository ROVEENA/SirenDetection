///////////////////////////////////////////////////////////
//  IRPortECU.h
//  Implementation of the Interface IRPortECU
//  Created on:      17-Jan-2023 22:59:56
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_7BE3FA52_1E52_4e08_BDF0_504B1C777E61__INCLUDED_)
#define EA_7BE3FA52_1E52_4e08_BDF0_504B1C777E61__INCLUDED_

#include "IfInECU.h"
#include "IPortLifeycle.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 17-Jan-2023 22:59:56
		 */
		class IRPortECU : public adlux::vse::IfInECU, public adlux::component_model::IPortLifeycle
		{


		};

	}

}
#endif // !defined(EA_7BE3FA52_1E52_4e08_BDF0_504B1C777E61__INCLUDED_)
