#include "../include/graph/VAOWrapper.h"
#include "../openglPriv.h"

#define VAO_LOG_DEBUG(x)	LOG_PRIVATE_DEBUG("VAOWrapper: "<<x)
#define VAO_LOG_ERROR(x)	LOG_PRIVATE_DEBUG_ERROR("VAOWrapper: "<<x)

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace ml
{
	namespace graph
	{
		VAOWrapper::VAOWrapper(const TriangleList &trList, const AttributeMap &attributeMap)
		{
			GL_(glGenVertexArrays(1, &Vao));

			GL_(glBindVertexArray(Vao));

			GL_(glGenBuffers(1, &VertexVBOID));

			GL_(glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID));
			GL_(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * trList.getData().size(), trList.getDataPointer(), GL_STATIC_DRAW));

			for (u32 index = 0; index < attributeMap.size(); ++index)
			{
				s32 size;
				u32 type;
				bool normalized;
				s32 stride;
				void *offset;

				if (attributeMap[index].size() > 0)
				{
					switch (index)
					{
					case AttributeType::Positions:
						size = 3;
						type = GL_FLOAT;
						normalized = GL_FALSE;
						stride = sizeof(Vertex);
						offset = BUFFER_OFFSET(0);
						break;
					case AttributeType::Colors:
						size = 4;
						type = GL_FLOAT;
						normalized = GL_FALSE;
						stride = sizeof(Vertex);
						offset = BUFFER_OFFSET(sizeof(Point));
						break;
					case AttributeType::Textcoord0:
						size = 2;
						type = GL_FLOAT;
						normalized = GL_FALSE;
						stride = sizeof(Vertex);
						offset = BUFFER_OFFSET(sizeof(Point) + sizeof(Color));
						break;
					default:
						break;
					}
					GL_(glVertexAttribPointer(index, size, type, normalized, stride, offset));
					GL_(glEnableVertexAttribArray(index));
				}
				else
				{
					// TO DO: Custom attributes.
				}
			}
			iSize = trList.getIndices().size();
			GL_(glGenBuffers(1, &IndexVBOID));
			GL_(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID));
			GL_(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u16) * iSize, trList.getIndicesPointer(), GL_STATIC_DRAW));


			GL_(glBindVertexArray(0));
		}

		VAOWrapper::~VAOWrapper()
		{
			if (Vao > 0 || VertexVBOID > 0 || IndexVBOID > 0)
			{
				if (Vao < 1 || VertexVBOID < 1 || IndexVBOID < 1)
				{
					VAO_LOG_ERROR("Corrupted or empty vao");
				}
				else
				{
					GL_(glDeleteVertexArrays(1, &(Vao)));
				}
			}
		}
	}
}
