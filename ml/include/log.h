#ifndef __LOG_H__
#define __LOG_H__

#define  __LEAK_DETECTOR__

#ifdef __LEAK_DETECTOR__
	#ifdef _DEBUG
		#define _NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	#endif
#endif

#ifndef NO_LOGS

#include <iostream>

#define LOG_DEBUG(params)	std::cout << params << std::endl;
#define LOG_INFO(params)	std::cout << params << std::endl;
#define LOG_MESSAGE(params)	std::cout << params << std::endl;
#define LOG_WARNING(params)	std::cout << params << std::endl;
#define LOG_ERROR(params)	std::cout << params << std::endl;

#endif

#endif
