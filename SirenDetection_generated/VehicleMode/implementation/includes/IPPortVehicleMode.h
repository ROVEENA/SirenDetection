///////////////////////////////////////////////////////////
//  IPPortVehicleMode.h
//  Implementation of the Interface IPPortVehicleMode
//  Created on:      17-Jan-2023 22:59:56
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_6C4D3389_4EE7_4493_9581_FCEA5C97EA6C__INCLUDED_)
#define EA_6C4D3389_4EE7_4493_9581_FCEA5C97EA6C__INCLUDED_

#include "IfOutVehicleMode.h"
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
		class IPPortVehicleMode : public adlux::vse::IfOutVehicleMode, public adlux::component_model::IPortLifeycle
		{

		};

	}

}
#endif // !defined(EA_6C4D3389_4EE7_4493_9581_FCEA5C97EA6C__INCLUDED_)
