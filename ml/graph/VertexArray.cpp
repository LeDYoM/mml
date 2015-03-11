#include "../include/graph/VertexArray.h"

namespace ml
{
	namespace graph
	{
		VertexArray::VertexArray()
		{
		}


		VertexArray::~VertexArray()
		{
		}

		VertexArray::VertexArray(const std::vector<Vertex> &data_)
		{
			data = data_;
		}

		VertexArray::VertexArray(const std::initializer_list<Vertex> &data) 
			:VertexArray(std::vector<Vertex>(data))
		{
		}

		VertexArray::VertexArray(VertexArray&&other)
		{
			data = std::move(other.data);
		}

		VertexArray & VertexArray::operator=(VertexArray&&other)
		{
			if (this != &other)
			{
				data = std::move(other.data);
			}

			return *this;
		}

		VertexArray &VertexArray::insert(const VertexArray&other)
		{
			data.insert(data.end(), other.data.begin(), other.data.end());
			return *this;
		}

		void VertexArray::clear()
		{
			data.clear();
		}
	}
}
