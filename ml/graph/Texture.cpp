#include "../include/graph/Texture.h"
#include "soil/SOIL.h"
#include "../mlprivcconfig.h"
#include "../openglPriv.h"

namespace ml
{
	namespace graph
	{
		Texture::Texture() : TextureOptions(), internalid(0)
		{
		}

		Texture::Texture(const std::string &fileName) : Texture()
		{
			if (!Load(fileName))
			{
				Remove();
			}
		}

		bool Texture::Load(const std::string &fileName)
		{
			internalid = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
			if (!isValid())
			{
				LOG_PRIVATE_DEBUG_ERROR("Error loading " << fileName);
			}
			return isValid();
		}

		bool Texture::Load(const Image &image)
		{
//			internalid = SOIL_create_OGL_texture(image.getRawData(), image.getSize().width, 
//				image.getSize().height,	image.getBPP(), 0, 0);
			//glHint (GL_GENERATE_MIPMAP_HINT, GL_NICEST);

			GL_(glGenTextures(1, &internalid));

			// Binds this texture handle so we can load the data into it
			GL_(glBindTexture(GL_TEXTURE_2D, internalid));

			GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));

			GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GL_(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));

			GL_(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x,
				image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
				image.getRawData()));

			GL_(glBindTexture(GL_TEXTURE_2D, 0));

			return isValid();
		}

		void Texture::Remove()
		{
			GL_(glDeleteTextures(1, &(internalid)));
			internalid = 0;
		}

		Texture::~Texture()
		{
			Remove();
		}

		Texture * Texture::fromImage(const Image &image)
		{
			Texture *resultT = new Texture();
			resultT->Load(image);
			return resultT;
		}

		void Texture::use() const
		{
			GL_(glEnable(GL_TEXTURE_2D));
			GL_(glBindTexture(GL_TEXTURE_2D, internalid));
			return;
			GL_(glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE));
			GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			if (mipmapping)
			{
				if (linear)
				{
					GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
					GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR));
				}
				else
				{
					GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
					GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST));
				}
			}
			else
			{
				if (linear)
				{
					GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
					GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				}
				else
				{
					GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
					GL_(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
				}
			}

			if (useAlpha)
			{
				GL_(glDisable(GL_ALPHA_TEST));
				GL_(glEnable(GL_BLEND));
				GL_(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			}
			else
			{
				GL_(glDisable(GL_BLEND));
			}
		}

		void Texture::unuse() const
		{
			GL_(glBindTexture(GL_TEXTURE_2D, 0));
			GL_(glDisable(GL_TEXTURE_2D));
		}

	}
}
