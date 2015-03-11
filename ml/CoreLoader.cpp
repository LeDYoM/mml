#include "include/CoreLoader.h"
#include "coreLoaderPriv.h"
#include "CorePriv.h"

namespace ml
{
	static priv::CorePriv *instance;

	bool LoadCore()
	{
		if (!instance)
		{
			instance = new priv::CorePriv();
			return true;
		}
		return false;
	}

	bool UnLoadCore()
	{
		if (instance)
		{
			delete instance;
			instance = 0;
			return true;
		}
		return false;
	}

	ml::Core *getCore()
	{
		return instance;
	}

	namespace priv
	{
		CorePriv *getPrivCore()
		{
			return instance;
		}
	}
}
