#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>
#include "../mlcconfig.h"

namespace ml
{
	namespace graph
	{
		class ML_API Resource
		{
		protected:
			Resource();
			virtual ~Resource();

			virtual bool Load(const std::string&) = 0;
			friend class ResourceManager;
		};
	}
}
#endif
