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
    void            changeCallbacksListener( CallbacksListener* p );

    int             setLogLevel( LogLevel level );
    LogLevel        getLogLevel();

    ConnectionState getConnectionState();
    bool            isReady();

    int             queryPurchasesAsync( ProductType product_type );
    int             queryProductDetailsAsync( ProductType product_type,
                                              std::list<std::string>* list );

    int             launchLoginFlowAsync();
    int             launchUpdateOrInstallFlow();

    int             launchPurchaseFlow( const char* product_id,
                                        ProductType product_type,
                                        const char* developer_payload,          // optional
                                        const char* product_name,               // optional
                                        const char* game_user_id,               // optional
                                        const int   quantity,
                                        const bool  promotion_applicable );
    int             launchUpdateSubscription( const char* product_id,
                                              const char* developer_payload,    // optional
                                              const char* product_name,         // optional
                                              const char* old_purchase_token,
                                              ProrationMode proration_mode );
    int             launchManageSubscription( PurchaseData* pData = nullptr );  // optional

    int             consumeAsync( PurchaseData* data );
    int             acknowledgeAsync( PurchaseData* data );

    int             manageRecurringProductAsync( PurchaseData* data, RecurringState state );

    int             getStoreInfoAsync();
    bool            verifyPurchaseData( const char* publicKey, PurchaseData* data );
    void            showToast( const char* fmt, ... );
    // OneStore IAP API end.
};

extern std::unique_ptr<Engine> NativeIapHelper;

}


#ifdef __cplusplus
}
#endif

