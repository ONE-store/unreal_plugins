/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include <jni.h>
#include <memory>

#include "ONEstoreIapCallbacksListener.h"
#include "ONEstoreIapEnums.h"
#include "ONEstoreIapError.h"
#include "ONEstoreIapResult.h"
#include "ONEstoreIapProductDetail.h"
#include "ONEstoreIapPurchaseData.h"
#include "ONEstoreIapPurchaseDataCore.h"


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------


#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP {

class Engine {
public:
    Engine();
    virtual ~Engine();

    // OneStore IAP API

    bool            init( JNIEnv* env, jobject activity, CallbacksListener* p = nullptr );
    void            changeCallbacksListener( CallbacksListener* p );

    int             setLogLevel( LogLevel level );
    LogLevel        getLogLevel();

    bool            isReady();

    std::unique_ptr<IapResult> isFeatureSupported( const char* feature );

    ConnectionState getConnectionState();


    // last product name must be terminate null.
    int             queryProductDetailsAsync( ProductType product_type,
                                              const char* productName,
                                              ... ) __attribute__((sentinel));

    int             queryProductDetailsAsync( ProductType product_type,
                                              std::list<std::string>& list );

    int             queryPurchasesAsync( ProductType product_type );

    int             launchLoginFlowAsync();
    int             launchSilentLoginFlow();

    int             launchUpdateOrInstallFlow();
    int             launchPurchaseFlow( const char* product_id,
                                        ProductType product_type,
                                        const char* developer_payload,
                                        const char* product_name,
                                        const char* game_user_id,
                                        const int   quantity,
                                        const bool  promotion_applicable );

    int             launchUpdateSubscription( const char* product_id,
                                              const char* developer_payload,
                                              const char* product_name,
                                              const char* old_purchase_token,
                                              ProrationMode proration_mode );

    int             acknowledgeAsync( PurchaseDataCore* p );
    int             consumeAsync( PurchaseDataCore* p );
    int             launchManageSubscription( PurchaseDataCore* p );
    int             manageRecurringProductAsync( PurchaseDataCore* p, RecurringState state );
    int             verifyPurchaseData( PurchaseDataCore* p, const char* publicKey );

    int             getStoreInfoAsync();
    void            showToast( const char* fmt, ... );

    // OneStore IAP API end.

};

extern std::unique_ptr<Engine> NativeIapHelper;

}


#ifdef __cplusplus
}
#endif

