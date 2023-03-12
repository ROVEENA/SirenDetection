///////////////////////////////////////////////////////////
//  IPPortShowAlert.h
//  Implementation of the Interface IPPortShowAlert
//  Created on:      18-Jan-2023 20:33:44
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_0080DCC5_24DC_4b22_ABD2_0111DAA44419__INCLUDED_)
#define EA_0080DCC5_24DC_4b22_ABD2_0111DAA44419__INCLUDED_

#include "IfOutShowAlert.h"
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
		class IPPortShowAlert : public adlux::vse::IfOutShowAlert, public adlux::component_model::IPortLifeycle
		{

		public:
			IPPortShowAlert() {

			}

			virtual ~IPPortShowAlert() {

			}

		};

	}

}
#endif // !defined(EA_0080DCC5_24DC_4b22_ABD2_0111DAA44419__INCLUDED_)
