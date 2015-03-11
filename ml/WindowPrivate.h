#ifndef __WINDOWPRIVATE_H__
#define __WINDOWPRIVATE_H__

#include "TWWrapper.h"

namespace ml
{
	namespace priv
	{
		struct WindowPrivate
		{
			TWWrapper *winWrapper{ 0 };
		};
	}
}

#endif
