///////////////////////////////////////////////////////////
//  IRPortEvVechicle.h
//  Implementation of the Interface IRPortEvVechicle
//  Created on:      18-Jan-2023 20:33:44
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_CF84CED1_686E_4aec_A2D6_6815172DC9B6__INCLUDED_)
#define EA_CF84CED1_686E_4aec_A2D6_6815172DC9B6__INCLUDED_

#include "IfInEVehicle.h"
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
		class IRPortEvVechicle : public adlux::vse::IfInEVehicle, public adlux::component_model::IPortLifeycle
		{

		public:
			IRPortEvVechicle() {

			}

			virtual ~IRPortEvVechicle() {

			}

		};

	}

}
#endif // !defined(EA_CF84CED1_686E_4aec_A2D6_6815172DC9B6__INCLUDED_)
