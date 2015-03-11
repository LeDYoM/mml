#include "../include/graph/Shader.h"
#include "../openglPriv.h"

#define SHADER_ERROR LOG_PRIVATE_DEBUG_ERROR
#define SHADER_INFO LOG_PRIVATE_DEBUG

namespace ml
{
	namespace graph
	{
		void printShaderInfoLog(GLint shader)
		{
			int infoLogLen = 0;
			int charsWritten = 0;
			GLchar *infoLog;

			GL_(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen));

			if (infoLogLen > 0)
			{
				infoLog = new GLchar[infoLogLen];
				// error check for fail to allocate memory omitted
				GL_(glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog));
				SHADER_ERROR(infoLog);
				delete[] infoLog;
			}
		}

		void Shader::readInfo()
		{
			char *name;
			GLint active, max_length;
			glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &active);
			glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_length);
			name = new char[max_length + 1];
			SHADER_INFO("Shader info:");
			SHADER_INFO("Attributes:");

			for (int i = 0; i < active; i++)
			{
				GLint size;
				GLenum type;
				glGetActiveAttrib(shaderProgram, i, max_length + 1, NULL, &size, &type, name);
				s32 loc = glGetAttribLocation(shaderProgram, name);
				attributes.push_back(std::make_pair(loc, name));
				SHADER_INFO("Attribute " << name << "("<<type<<") is at location " << loc);
			}
			delete[] name;

			glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &active);
			glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
			name = new char[max_length + 1];
			SHADER_INFO("Uniforms:");

			for (int i = 0; i < active; i++)
			{
				GLint size;
				GLenum type;
				glGetActiveUniform(shaderProgram, i, max_length + 1, NULL, &size, &type, name);
				s32 loc = glGetUniformLocation(shaderProgram, name);
				attributes.push_back(std::make_pair(loc, name));
				SHADER_INFO("Uniform " << name << "(" << type << ") is at location " << loc);
			}

			delete[] name;
		}

		Shader::Shader() : shaderProgram(0), vertexShader(0), fragmentShader(0)
		{
		}

		Shader::Shader(const std::string &vShaderCode, const std::string &fShaderCode, 
			const AttributeMap &attributes)
			: Shader()
		{
			int result = LoadShader(vShaderCode, fShaderCode, attributes);
		}

		Shader::~Shader()
		{
			destroy();
		}

		bool Shader::LoadShader(const std::string &vShaderCode, const std::string &fShaderCode,
			const AttributeMap &attributes)
		{
			// load shaders & get length of each
			int vlen;
			int flen;

			vlen = vShaderCode.length();
			flen = fShaderCode.length();

			if (vShaderCode.empty())
			{
				SHADER_ERROR("Vertex shader code is empty");
				return false;
			}

			if (fShaderCode.empty())
			{
				SHADER_ERROR("Fragment shader code is empty");
				return false;
			}

			vertexShader = GL_(glCreateShader(GL_VERTEX_SHADER));
			fragmentShader = GL_(glCreateShader(GL_FRAGMENT_SHADER));

			const char *vertexShaderCStr = vShaderCode.c_str();
			const char *fragmentShaderCStr = fShaderCode.c_str();
			GL_(glShaderSource(vertexShader, 1, (const GLchar **)&vertexShaderCStr, &vlen));
			GL_(glShaderSource(fragmentShader, 1, (const GLchar **)&fragmentShaderCStr, &flen));

			GLint compiled;

			GL_(glCompileShader(vertexShader));
			GL_(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled));
			SHADER_INFO("Vertex shader compile result:");
			printShaderInfoLog(vertexShader);
			if (compiled == GL_FALSE)
			{
				SHADER_ERROR("Vertex shader not compiled");
				destroy();
				return false;
			}

			GL_(glCompileShader(fragmentShader));
			GL_(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled));
			SHADER_INFO("Fragment shader compile result:");
			printShaderInfoLog(fragmentShader);

			if (compiled == GL_FALSE)
			{
				SHADER_ERROR("Fragment shader not compiled.");
				destroy();
				return false;
			}

			GL_(shaderProgram = glCreateProgram());

			GL_(glAttachShader(shaderProgram, vertexShader));
			GL_(glAttachShader(shaderProgram, fragmentShader));
			
			if (attributes.size() > 0)
			{
				for (u32 i = 0; i < attributes.size();++i)
				{
					if (attributes[i].size() > 0)
					{
						GL_(glBindAttribLocation(shaderProgram, i, attributes[i].c_str()));
						SHADER_INFO("Bound attribute " << i << " to " << attributes[i]);
					}
				}
			}
			glLinkProgram(shaderProgram);

			GLint IsLinked;
			GL_(glGetProgramiv(shaderProgram, GL_LINK_STATUS, (GLint *)&IsLinked));
			if (IsLinked == GL_FALSE)
			{
				SHADER_ERROR("Failed to link shader");
				printShaderInfoLog(shaderProgram);
				destroy();

				return false;
			}

			readInfo();
			return true;
		}

		void Shader::destroy()
		{
			if (shaderProgram > 0)
			{
				GL_(glDetachShader(shaderProgram, vertexShader));
				GL_(glDetachShader(shaderProgram, fragmentShader));
			}

			destroyVertAndFragment();

			if (shaderProgram > 0)
			{
				GL_(glDeleteProgram(shaderProgram));
				shaderProgram = 0;
			}
		}

		void Shader::destroyVertAndFragment()
		{
			if (vertexShader > 0)
			{
				GL_(glDeleteShader(vertexShader));
				vertexShader = 0;
			}

			if (fragmentShader > 0)
			{
				GL_(glDeleteShader(fragmentShader));
				fragmentShader = 0;
			}
		}

		void Shader::use()
		{
			GL_(glUseProgram(shaderProgram));
		}

		void Shader::unuse()
		{
			GL_(glUseProgram(0));
		}

		bool Shader::setUniformf32(const std::string &uName, const f32 value)
		{
			GLint loc;
			if (getUniform(uName,&loc))
			{
				GL_(glUniform1f (loc, value));
				return true;
			}
			return false;
		}

		bool Shader::setUniformColor(const std::string &uName, const Color &color)
		{
			return setUniform4f32(uName, color.r,color.g,color.b,color.a);
		}

		bool Shader::setUniformVector3d(const std::string &uName, const Vector3d<f32> &v)
		{
			return setUniform4f32(uName, v.x, v.y, v.z, 0.0f);
		}

		bool Shader::setUniform4f32(const std::string &uName, const f32 value0, f32 value1, f32 value2, f32 value3)
		{
			GLint loc;
			if (getUniform(uName, &loc))
			{
				GL_(glUniform4f(loc, value0, value1, value2, value3));
				return true;
			}
			return false;
		}

		bool Shader::setUniform4f32(const std::string &uName, const f32 *value)
		{
			GLint loc;
			if (getUniform(uName, &loc))
			{
				GL_(glUniform4fv(loc, 0, value));
				return true;
			}
			return false;
		}

		bool Shader::setUniform1i(const std::string &uName, const s32 value)
		{
			GLint loc;
			if (getUniform(uName, &loc))
			{
				GL_(glUniform1i(loc, value));
				return true;
			}
			return false;
		}

		bool Shader::setUniformMatrix4f32(const std::string uName, const Matrix<f32, 4> &matrix)
		{
			GLint loc;
			if (getUniform(uName, &loc))
			{
				GL_(glUniformMatrix4fv(loc, 1, false, matrix.raw()));
				return true;
			}
			return false;
		}

		bool Shader::setTextureUniform(const std::string uName, const Texture &texture)
		{
			return setUniform1i(uName, texture.id());
		}

		bool Shader::getUniform(const std::string &uName, s32 *loc)
		{
			*loc = glGetUniformLocation(shaderProgram, uName.c_str());
			_GL(;);
			if (*loc < 0)
			{
				LOG_PRIVATE_DEBUG_ERROR("The uniform " << uName << " is not found on this shader");
				return false;
			}
			else
			{
				return true;
			}
		}


	}
}
