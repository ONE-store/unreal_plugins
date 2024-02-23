/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include <jni.h>
#include <list>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif


namespace ONESTORE_IAP{

enum class PurchaseState;
enum class RecurringState;

class PurchaseData{
public:
    PurchaseData( jobject obj );

    virtual ~PurchaseData();

    const char*     getOriginalJson();

    const char*     getOrderId();

    const char*     getPackageName();

    const char*     getProductId();

    const char*     getDeveloperPayload();

    const char*     getPurchaseId();

    const char*     getPurchaseToken();

    const char*     getBillingKey();

    const char*     getSignature();

    bool            isAcknowledged();

    int32_t         getQuantity();

    int64_t         getPurchaseTime();

    PurchaseState   getPurchaseState();

    RecurringState  getRecurringState();

    virtual void    dump();
};

}

#ifdef __cplusplus
}
#endif
