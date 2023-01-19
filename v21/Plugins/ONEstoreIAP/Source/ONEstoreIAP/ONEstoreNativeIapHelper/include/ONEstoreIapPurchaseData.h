/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include <jni.h>
#include <list>
#include <string>

#include "ONEstoreIapObject.h"


#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP{

    enum class PurchaseState;
    enum class RecurringState;

    class PurchaseData : public IapObject{
    public:
        PurchaseData();
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

        int             getQuantity();

        int64_t         getPurchaseTime();

        PurchaseState   getPurchaseState();

        RecurringState  getRecurringState();

        virtual void    dump();

        static std::unique_ptr<PurchaseData> getPurchaseData( jobject );
        static std::unique_ptr<std::list<PurchaseData>> getPurchaseDataList( jobject );
        static std::unique_ptr<jobject> getPurchaseDataObj( const char*, const char*, const char* );
        static std::unique_ptr<jobject> getPurchaseDataObj( PurchaseData* pData );

    protected:
        std::string     OrigJson;
        std::string     OrderId;
        std::string     PackageName;
        std::string     ProductId;
        std::string     DeveloperPayload;
        std::string     PurchaseId;
        std::string     PurchaseToken;
        std::string     BillingKey;
        std::string     Signature;

        bool            IsAcknowledged;
        int             Quantity;
        int64_t         PurchaseTime;
        PurchaseState   purchaseState;
        RecurringState  recurringState;


    public:
        static jclass   purchaseDataClass;
        static void     NewGlobalRef();
        static void     clearGlobalRef();

    };

}

#ifdef __cplusplus
}
#endif
