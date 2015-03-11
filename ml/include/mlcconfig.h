#ifndef __MLCCONFIG_H__
#define __MLCCONFIG_H__

#ifdef ML_EXPORTS
#define ML_API __declspec(dllexport)
#else
#define ML_API __declspec(dllimport)
#endif

#endif
