/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP{

#ifndef check
#define check               say("");
#endif

#ifndef say
#define say( ... )          _log1( __FILE__, __FUNCTION__, __LINE__, (const char*)__VA_ARGS__ )
#endif

#ifndef say_check
#define say_check           _log1( __FILE__, __FUNCTION__, __LINE__, (const char*)"" )
#endif

#ifndef say2
#define say2( ... )         _log2( (const char*)__VA_ARGS__ )
#endif


extern int SAY_LOGLEVEL;
extern void _log1( const char* lpfile, const char* lpfn, int line, const char *fmt, ... );
extern void _log2( const char *fmt, ... );
}

#ifdef __cplusplus
}
#endif
