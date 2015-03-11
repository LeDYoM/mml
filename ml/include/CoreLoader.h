#ifndef __CORELOADER_H__
#define __CORELOADER_H__

#include "mlcconfig.h"

namespace ml
{
	class Core;
	ML_API bool LoadCore();
	ML_API bool UnLoadCore();
	ML_API ml::Core *getCore();
}

#endif
