///////////////////////////////////////////////////////////
//  IRPortVehicleMode.h
//  Implementation of the Interface IRPortVehicleMode
//  Created on:      18-Jan-2023 20:33:44
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_59B22BA7_F542_47b3_A358_C6EA0E0BD319__INCLUDED_)
#define EA_59B22BA7_F542_47b3_A358_C6EA0E0BD319__INCLUDED_

#include "IfInVehicleMode.h"
#include "IPortLifeycle.h"

namespace adlux
{
	namespace vse
	{
		/**
		 * @author RLobo
		 * @version 1.0
		 * @created 18-Jan-2023 20:33:44
		 */
		class IRPortVehicleMode : public adlux::vse::IfInVehicleMode, public adlux::component_model::IPortLifeycle
		{

		public:
			IRPortVehicleMode() {

			}

			virtual ~IRPortVehicleMode() {

			}

		};

	}

}
#endif // !defined(EA_59B22BA7_F542_47b3_A358_C6EA0E0BD319__INCLUDED_)
