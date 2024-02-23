/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP{

class PurchaseDataCore{
public:
    PurchaseDataCore( const char* json,
                      const char* signature,
                      const char* billingKey );

    virtual ~PurchaseDataCore();

    const char* getBillingKey();
    const char* getOriginalJson();
    const char* getSignature();
    virtual void dump();
};

}

#ifdef __cplusplus
}
#endif
