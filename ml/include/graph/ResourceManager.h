#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <list>
#include "TriangleList.h"
#include "Shape.h"
#include "BMText.h"
#include "../include/mlcconfig.h"

namespace ml
{
	namespace graph
	{
		template class ML_API std::list < Shape* >;
		template class ML_API std::list < Resource* > ;

		class ML_API ResourceManager
		{
		public:
			ResourceManager();
			virtual ~ResourceManager();

			template <class T> T *loadResource(const std::string &fileName)
			{
				T *t = _NEW T();
				bool result = t->Load(fileName);
				if (result)
				{
					resources.push_back(t);
					return t;
				}
				else
				{
					delete t;
					return nullptr;
				}
			}

			BMText *print(const BMFont *font, const std::string &str);

			template <class T> T *newShape()
			{
				T *temp = _NEW T();
				shapes.push_back(temp);
				return temp;
			}

		private:
			std::list<Shape*> shapes;
			std::list<Resource*> resources;

		};
	}
}
#endif

