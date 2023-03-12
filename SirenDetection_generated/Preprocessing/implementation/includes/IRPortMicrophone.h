///////////////////////////////////////////////////////////
//  IRPortMicrophone.h
//  Implementation of the Interface IRPortMicrophone
//  Created on:      18-Jan-2023 12:21:55
//  Original author: RLobo
///////////////////////////////////////////////////////////

#if !defined(EA_5ED017BE_A5E3_477a_B8A7_1DEA20D9E537__INCLUDED_)
#define EA_5ED017BE_A5E3_477a_B8A7_1DEA20D9E537__INCLUDED_

#include "IfInMicrphone.h"
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
		class IRPortMicrophone : public adlux::vse::IfInMicrphone, public adlux::component_model::IPortLifeycle
		{

		};

	}

}
#endif // !defined(EA_5ED017BE_A5E3_477a_B8A7_1DEA20D9E537__INCLUDED_)
