#include "../include/graph/RenderManager.h"
#include "../include/Matrix.h"
#include "../include/graph/Shape.h"
#include "../include/graph/Texture.h"
#include "../include/graph/bmfont.h"
#include "../include/graph/BMText.h"
#include "../openglPriv.h"

#include "../include/graph/Shader.h"
#include "../include/graph/VAOWrapper.h"

#define RM_LOG_DEBUG(x)	LOG_PRIVATE_DEBUG("RenderManager: "<<x)
#define RM_LOG_ERROR(x)	LOG_PRIVATE_DEBUG_ERROR("RenderManager: "<<x)

#define __USEVBO__

namespace ml
{
	namespace graph
	{
		RenderManager::RenderManager()
		{
		}

		RenderManager::~RenderManager()
		{

		}

		void RenderManager::registerForRender(Shape &shape)
		{
			initVAO(shape.getTriangleList());
		}

		void RenderManager::unRegisterForRender(Shape &shape)
		{

		}

		void RenderManager::applyModelViewTransform(const TransformationMatrix &mvm)
		{
			modelViewMatrix = mvm;
		}

		void RenderManager::Init()
		{
			GL_(glDisable(GL_BLEND));
		}

		void RenderManager::Clear()
		{
			GL_(glClear(GL_COLOR_BUFFER_BIT));
		}

		void ViewOrtho(int width, int height)
		{

			glViewport(0, 0, width, height);             // Set Up An Ortho View	 
			glMatrixMode(GL_PROJECTION);			  // Select Projection
			glLoadIdentity();						  // Reset The Matrix
			glOrtho(0, width, height, 0, -1, 1);	  // Select Ortho 2D Mode (640x480)
			glMatrixMode(GL_MODELVIEW);				  // Select Modelview Matrix
			glLoadIdentity();						  // Reset The Matrix
		}

		void RenderManager::setPerspective(const TransformationMatrix &m)
		{
//			GL_(glMatrixMode(GL_PROJECTION));

//			GL_(glLoadMatrixf(m.raw()));
//			ViewOrtho(640, 480);
			projectionMatrix = m;
			GL_(glMatrixMode(GL_MODELVIEW));
			GL_(glLoadIdentity());
		}

		void RenderManager::setPerspective(const Rectanglef32 &perspective)
		{
			projectionMatrix.setOrtho(perspective.x, perspective.x2,
				perspective.y, perspective.y2, 1.0, -1.0f);
		}

		void RenderManager::setViewPort(const Rectangleu32 &viewPort)
		{
			GL_(glMatrixMode(GL_PROJECTION));
			GL_(glViewport(viewPort.x, viewPort.y, viewPort.width(), viewPort.height()));
		}

		VertexArray pvertex;
//		TriangleList trList;
//		GLuint VertexVBOID;
//		GLuint IndexVBOID;
//		GLuint Vao;

		Shader *shader;

		AttributeMap attributeMap = {
			"vPosition",		// Position : 0
			"",				// TO DO: Normals : 1
			"",				// Empty: 2
			"vColor",		// Color : 3
			"",				// Empty : 4
			"",				// Empty : 5
			"",				// Empty : 6
			"",				// Empty : 7
			"textCoord"		// TextCoord0 : 8

		};

		void initShaders()
		{
			std::string vertexShaderString = "#version 330\n\
				in vec4 vPosition;\n\
				in vec4 vColor;\n\
				in vec2 textCoord;\n\
				uniform mat4 projectionMatrix;\n\
				uniform mat4 modelViewMatrix;\n\
				out vec4 ex_Color;\n\
				out vec2 vTextCoord;\n\
				void main(void) {\n\
					gl_Position = projectionMatrix * modelViewMatrix * vPosition;\n\
					ex_Color = vColor;\n\
					vTextCoord = textCoord;\n\
				}\n";

			std::string fragmentShaderString = "#version 330\n\
				precision highp float;\n\
				in vec4 ex_Color;\n\
				in vec2 vTextCoord;\n\
				uniform sampler2D texture;\n\
				void main(void) {\n\
					gl_FragColor = texture2D(texture, vTextCoord.st);\n\
					//gl_FragColor = gl_FragColor * ex_Color;\n\
					//gl_FragColor = ex_Color;\n\
					//gl_FragColor = vec4(vTextCoord, 0.0, 0.0);\n\
				}\n";

			shader = _NEW Shader(vertexShaderString, fragmentShaderString, attributeMap);
		}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

		VAOWrapper *RenderManager::initVAO(const TriangleList &trList)
		{
			//VERTEX 0
			pvertex.data.push_back(Vertex(Point(0.0f, 0.0f, 0.0f),Color(1.0f,0.0f,0.0f,1.0f),Point2d(0.0f,0.0f)));
			//VERTEX 1
			pvertex.data.push_back(Vertex(Point(601.0f, 0.0f, 0.0f), Color(0.0f, 1.0f, 0.0f, 1.0f), Point2d(1.0f, 1.0f)));
			//VERTEX 2
			pvertex.data.push_back(Vertex(Point(0.0f, 100.0f, 0.0f), Color(0.0f, 0.0f, 1.0f, 1.0f), Point2d(0.5f, 0.5f)));
//			trList.add(pvertex);
			//Define this somewhere in your header file

			VAOWrapper *VAOWTemp = _NEW VAOWrapper(trList, attributeMap);
			return VAOWTemp;
		}

		void RenderManager::deleteVAO(VAOWrapper *vaow)
		{
			delete vaow;
		}

		static bool initialized = false;

		void RenderManager::RenderVAO(VAOWrapper *vaow, const Texture *texture)
		{
#ifdef __USEVBO__
//			if (!trList.vaow)
//			{
//				initVAO(trList);
//				trList.vbo = _NEW VBOWrapper(trList);
//			}
			if (!initialized)
			{
//				init(trList);
				initShaders();
				initialized = true;
			}

			shader->use();
			GL_(glBindVertexArray(vaow->Vao));


			if (texture)
			{
				GL_(glActiveTexture(GL_TEXTURE0 + 0));
				GL_(glBindTexture(GL_TEXTURE_2D, texture->id())); //Use the same sampler as before.
//				shader->setTextureUniform("texture",0);
				shader->setUniform1i("texture", 0);
			}

			shader->setUniformMatrix4f32("projectionMatrix", projectionMatrix);
//			currentPosition.x += 0.001f;
			shader->setUniformMatrix4f32("modelViewMatrix", modelViewMatrix);
//			shader->setUniformVector3d("scale", currentScale);
//			shader->setUniformVector3d("rotation", currentRotation);


			GL_(glDrawElements(GL_TRIANGLES, vaow->iSize, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0)));

			if (texture)
			{
				texture->unuse();
			}

			GL_(glBindVertexArray(0));
			shader->unuse();

			return;

#else

			if (texture)
			{
				texture->use();
				GL_(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
				GL_(glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), trList.getTextureCoordinatesPointer()));
			}

			//Enable Client States
			GL_(glEnableClientState(GL_VERTEX_ARRAY));
			GL_(glVertexPointer(3, GL_FLOAT, sizeof(Vertex), trList.getPositionsPointer()));

			GL_(glEnableClientState(GL_COLOR_ARRAY));
			GL_(glColorPointer(4, GL_FLOAT, sizeof(Vertex), trList.getColorsPointer()));
			GL_(glDrawElements(GL_TRIANGLES, trList.getIndices().size(), GL_UNSIGNED_SHORT, trList.getIndicesPointer()));

			// Finished Drawing, disable client states.
			GL_(glDisableClientState(GL_VERTEX_ARRAY));
			GL_(glDisableClientState(GL_COLOR_ARRAY));

			if (texture)
			{
				GL_(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
				texture->unuse();
			}

#endif
		}
	}
}
