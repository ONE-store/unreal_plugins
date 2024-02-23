/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include <jni.h>
#include <memory>
#include "ONEstoreAlcCallbacksListener.h"

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_ALC {


class Engine {
public:
    Engine();
    virtual ~Engine();

    bool            init( JNIEnv* env, jobject activity, CallbacksListener* p = nullptr );
    void            changeCallbacksListener( CallbacksListener* p );

    // OneStore ALC API
    int             queryLicense( const char* publicKey );
    int             strictQueryLicense( const char* publicKey );
    int             destroy();
    void            showToast( const char* fmt, ... );
    // OneStore ALC API end.
};

extern std::unique_ptr <Engine> NativeAlcHelper;
}


#ifdef __cplusplus
}
#endif

