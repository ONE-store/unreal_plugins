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

class IapObject;
class IapResult;
class PurchaseData;
class ProductDetail;

enum class LogLevel;
enum class ConnectionState;
enum class ProductType;
enum class ProrationMode;
enum class RecurringState;

class CallbacksListener {
public:
    // callback of acknowledgeAsync()
    virtual void onAcknowledgeAsync(IapResult *, PurchaseData *) PURE;

    // callback of consumeAsync()
    virtual void onConsumeAsync(IapResult *, PurchaseData *) PURE;

    // callback of launchLoginFlowAsync()
    virtual void onLaunchLoginFlowAsync(IapResult *) PURE;

    // callback of launchUpdateOrInstallFlow()
    virtual void onLaunchUpdateOrInstallFlow(IapResult *) PURE;

    // callback of manageRecurringProductAsync()
    virtual void onManageRecurringProductAsync(IapResult *, PurchaseData *, RecurringState) PURE;

    // callback of launchPurchaseFlow(), launchUpdateSubscription
    virtual void onPurchasesUpdated(IapResult *, std::list <PurchaseData> *) PURE;

    // callback of queryProductDetailsAsync()
    virtual void onQueryProductDetailsAsync(IapResult *, std::list <ProductDetail> *) PURE;

    // callback of queryPurchasesAsync()
    virtual void onQueryPurchasesAsync(IapResult *, std::list <PurchaseData> *) PURE;

    // callback of service disconnection
    virtual void onServiceDisconnected() PURE;

    // callback of startConnection()
    virtual void onSetupFinished(IapResult *) PURE;

    // callback of getStoreInfoAsync()
    virtual void onStoreInfoAsync(IapResult *, const char* ) PURE;

protected:
    void dump(IapObject *p);
};

}


#ifdef __cplusplus
}
#endif
