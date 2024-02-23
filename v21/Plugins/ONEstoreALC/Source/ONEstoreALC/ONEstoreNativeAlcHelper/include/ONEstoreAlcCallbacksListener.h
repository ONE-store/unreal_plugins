/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_ALC {

#ifndef PURE
#define PURE    =0;
#endif


class CallbacksListener {
public:
    virtual void onGranted(const char* license, const char* signature) PURE;
    virtual void onDenied() PURE;
    virtual void onError(int code, const char* msg) PURE;
};

}


#ifdef __cplusplus
}
#endif
