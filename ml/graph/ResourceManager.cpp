#include "../include/graph/ResourceManager.h"
#include "../logPriv.h"

#define RM_INFO(x)		LOG_PRIVATE_DEBUG("ResourceManager: "<<x)
namespace ml
{
	namespace graph
	{
		ResourceManager::ResourceManager()
		{
		}


		ResourceManager::~ResourceManager()
		{
			RM_INFO("Deleting shape list");
			for (std::list<Shape*>::iterator it = shapes.begin(); it != shapes.end();++it)
			{
				delete (*it);
			}
			shapes.clear();

			RM_INFO("Deleting resource list");
			for (std::list<Resource*>::iterator it = resources.begin(); it != resources.end(); ++it)
			{
				delete (*it);
			}
			resources.clear();

		}

		BMText * ResourceManager::print(const BMFont *font, const std::string &str)
		{
//			BMText *text = font->print(str);
			BMText *text = newShape<BMText>();
			text->Init(font, str);
			return text;
		}

	}
}
