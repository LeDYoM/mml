#ifndef __LOGPRIV_H__
#define __LOGPRIV_H__

#include "include/log.h"

#ifndef NO_PRIVATE_LOGS

	#include <iostream>
	#include <sstream>
void logOutput(const std::string &);

	#define PREPARE_PRIVATE_LOG(params) { std::ostringstream os_; os_ << params << std::endl; logOutput(os_.str()); }

	#define LOG_PRIVATE_DEBUG(params)	PREPARE_PRIVATE_LOG(params);
	#define LOG_PRIVATE_DEBUG_ERROR(params)	PREPARE_PRIVATE_LOG(params);
	#define LOG_PRIVATE_DEBUG_WARNING(params)	PREPARE_PRIVATE_LOG(params);

	#define ASSERT_PRIVATE_DEBUG(condition,message)	if (!(condition)) LOG_DEBUG_ERROR(message)

#else
	#define LOG_PRIVATE_DEBUG(params)
	#define LOG_PRIVATE_DEBUG_ERROR(params)
	#define LOG_PRIVATE_DEBUG_WARNING(params)

	#define ASSERT_PRIVATE_DEBUG(condition,message)

#endif

#endif
