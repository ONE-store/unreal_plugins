/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include <jni.h>


#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP{

enum class LogLevel{
    VERBOSE = 2,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    ASSERT
};

enum class ConnectionState{
    DISCONNECTED = 0,
    CONNECTING,
    CONNECTED,
    CLOSED
};


enum class PurchaseState{
    UNSPECIFIED_STATE = -1,
    PURCHASED,
    CANCEL,
    REFUND
};


enum class AcknowledgeState{
    UNSPECIFIED_STATE = -1,
    NOT_ACKNOWLEDGED,
    ACKNOWLEDGED
};


enum class RecurringState{
    NON_AUTO_PRODUCT = -1,
    RECURRING,
    CANCEL
};


enum class ProductType{
    UNKNOWN = -1,
    INAPP,          //"inapp"
    AUTO,           //"auto"
    SUBS,           //"subscription
    ALL             //"all"
};


enum class ProrationMode{
    UNKNOWN_SUBSCRIPTION_UPGRADE_DOWNGRADE_POLICY = 0,

    /**
     * 교체가 즉시 적용되며, 새로운 만료 시간은 비례 배분되어 사용자에게 입금되거나 청구됩니다.
     * 이는 현재 기본 동작입니다.
     */
    IMMEDIATE_WITH_TIME_PRORATION,

    /**
     * 교체가 즉시 적용되며 청구 주기는 동일하게 유지됩니다. 나머지 기간에 대한 가격이 청구됩니다.
     * 이 옵션은 구독 업그레이드에만 사용할 수 있습니다.
     */
    IMMEDIATE_AND_CHARGE_PRORATED_PRICE,
    /**
     * 교체가 즉시 적용되며 다음 결제일에 새로운 가격이 청구됩니다.
     * 청구 주기는 동일하게 유지됩니다.
     */

    IMMEDIATE_WITHOUT_PRORATION,

    /**
     * 기존 요금제가 만료되면 교체가 적용되며 새 요금이 동시에 청구됩니다.
     */
    DEFERRED
};


}


#ifdef __cplusplus
}
#endif
