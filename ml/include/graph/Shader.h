#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include "../types.h"
#include "../include/Matrix.h"
#include "Texture.h"

namespace ml
{
	namespace graph
	{
		class Shader
		{
		public:
			Shader();
			Shader(const std::string &vShaderCode, const std::string &fShaderCode,
				const AttributeMap &attributeMap);
			virtual ~Shader();

			u32 shaderProgram;
			u32 vertexShader;
			u32 fragmentShader;
			void destroyVertAndFragment();
			void destroy();

			void use();
			void unuse();

			// Set uniforms interface
			bool setUniformf32(const std::string &uName, const f32 value);
			bool setUniformColor(const std::string &uName, const Color &color);
			bool setUniformVector2d(const std::string &uName, const Vector2d<f32> &v);
			bool setUniformVector3d(const std::string &uName, const Vector3d<f32> &v);
			bool setUniform4f32(const std::string &uName, const f32 value0,f32 value1, f32 value2, f32 value3);
			bool setUniform4f32(const std::string &uName, const f32 *value);
			bool setUniform1i(const std::string &uName, const s32 value);
			bool setUniformMatrix4f32(const std::string uName, const Matrix<f32, 4> &matrix);
			bool setTextureUniform(const std::string uName, const Texture &texture);

		private:
			bool getUniform(const std::string &, s32 *loc);
			bool LoadShader(const std::string &vShaderCode, const std::string &fShaderCode, const AttributeMap &attributeMap);
			std::vector<std::pair<s32, std::string>> attributes;
			std::vector<std::pair<s32, std::string>> uniforms;

			void readInfo();
		};
	}
}

#endif
