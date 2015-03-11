#include "TWrapperLoader.h"
#include "mlprivcconfig.h"

#ifdef WINDOW_AND_INPUT_SYSTEM_GLFW
#include "wr_glfw/twglfw.h"
namespace ml
{
	namespace priv
	{
		typedef twglfw SelectedWindowInputWrapper;
	}
}

#endif

namespace ml
{
	namespace priv
	{
		TWrapperLoader::TWrapperLoader()
		{
		}


		TWrapperLoader::~TWrapperLoader()
		{
		}

		TWrapper * TWrapperLoader::createWindowAndInputWrapper()
		{
			SelectedWindowInputWrapper *sww = new SelectedWindowInputWrapper();
			return sww;
		}

	}
}
