#ifndef __VAOWRAPPER_H__
#define __VAOWRAPPER_H__

#include "TriangleList.h"

namespace ml
{
	namespace graph
	{
		class VAOWrapper
		{
		public:
			u32 Vao;
			u32 VertexVBOID;
			u32 IndexVBOID;
			u32 iSize;

			VAOWrapper(const TriangleList &from, const AttributeMap &attributeMap);
			~VAOWrapper();
		};
	}
}

#endif
