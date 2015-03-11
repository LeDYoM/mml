#ifndef __OPENGLPRIV_H__
#define __OPENGLPRIV_H__

#include "mlprivcconfig.h"

#ifndef __gl_h_

#if !defined(WINGDIAPI) && defined(_WIN32)
	#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__POCC__)
		#define WINGDIAPI __declspec(dllimport)
	#elif defined(__LCC__)
		#define WINGDIAPI __stdcall
	#else
		#define WINGDIAPI extern
	#endif
#endif

#ifndef APIENTRY
	#ifdef _WIN32
		#define APIENTRY __stdcall
	#else
		#define APIENTRY
	#endif
#endif /* APIENTRY */


#include "glew/glew.h"
//#include <gl/GL.h>
//#define GL_GLEXT_PROTOTYPES
//#include "../glext.h"

#endif

#ifdef CHECK_OPENGL_ERRORS

namespace ml
{
	namespace priv
	{
		void glCheckError(const char* file, unsigned int line);

		#define GL_(x) x; ml::priv::glCheckError(__FILE__, __LINE__);
		#define _GL(x) ml::priv::glCheckError(__FILE__, __LINE__); x;
		#define _GL_(x) ml::priv::glCheckError(__FILE__, __LINE__); x; ml::priv::glCheckError(__FILE__, __LINE__);
	}
}
#else
	#define GL_(x) x;
	#define _GL(x) x;
	#define _GL_(x) x;
#endif

#endif
