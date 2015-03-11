#ifndef __TWRAPPERLOADER_H__
#define __TWRAPPERLOADER_H__

#include "TWrapper.h"

namespace ml
{
	namespace priv
	{
		class TWrapperLoader
		{
		public:
			TWrapperLoader();
			~TWrapperLoader();

			TWrapper *createWindowAndInputWrapper();
		};
	}
}

#endif
