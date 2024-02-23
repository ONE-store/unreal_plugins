/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include <jni.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SIG_IAPRESULT
#define SIG_IAPRESULT                       "Lcom/gaa/sdk/iap/IapResult;"
#endif


namespace ONESTORE_IAP{

enum class ResponseCode;

class IapResult{
public:
    IapResult(jobject obj);

    IapResult(int _n, const char* _s = nullptr );

    IapResult(ResponseCode _n, const char* _s = nullptr );

    virtual ~IapResult();

    ResponseCode    getResponseCode();

    const char*     getMessage();

    bool            isSuccess();

    bool            isFailure();

    virtual void    dump();

    static std::unique_ptr<IapResult> getIapResult( jobject obj );

public:
    int             code;
    std::string     message;
};

}

#ifdef __cplusplus
}
#endif
