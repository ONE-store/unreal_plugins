/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include <list>

#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP {

#ifndef PURE
#define PURE    =0;
#endif

class IapResult;
class PurchaseData;
class ProductDetail;

enum class RecurringState;

class CallbacksListener {
public:
    // callback of acknowledgeAsync()
    virtual void onAcknowledgeResponse(IapResult *, PurchaseData *) PURE;

    // callback of consumeAsync()
    virtual void onConsumeResponse(IapResult *, PurchaseData *) PURE;

    // callback of launchLoginFlowAsync()
    virtual void onLaunchLoginFlowResponse(IapResult *) PURE;

    // callback of launchUpdateOrInstallFlow()
    virtual void onLaunchUpdateOrInstallFlowResponse(IapResult *) PURE;

    // callback of queryProductDetailsAsync()
    virtual void onProductDetailsResponse(IapResult *, std::list <ProductDetail> *) PURE;

    // callback of queryPurchasesAsync()
    virtual void onPurchasesResponse(IapResult *, std::list <PurchaseData> *) PURE;

    // callback of launchPurchaseFlow()
    virtual void onPurchasesUpdated(IapResult *, std::list <PurchaseData> *) PURE;

    // callback of service disconnection
    virtual void onServiceDisconnected() PURE;

    // callback of startConnection()
    virtual void onSetupFinished(IapResult *) PURE;

    // callback of getStoreInfoAsync()
    virtual void onStoreInfoResponse(IapResult *, const char* ) PURE;

    // callback of manageRecurringProductAsync()
    virtual void onRecurringResponse(IapResult *, PurchaseData *, RecurringState) PURE;
};

}


#ifdef __cplusplus
}
#endif
