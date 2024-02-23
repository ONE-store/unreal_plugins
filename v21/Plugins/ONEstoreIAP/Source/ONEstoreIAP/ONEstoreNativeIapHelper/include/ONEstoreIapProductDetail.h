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

namespace ONESTORE_IAP {

enum class ProductType;

class ProductDetail{
public:
    ProductDetail();
    ProductDetail(jobject obj);

    virtual ~ProductDetail();

    const char*     getOriginalJson();

    const char*     getProductId();

    ProductType     getType();

    const char*     getTitle();

    const char*     getPrice();

    const char*     getPriceCurrencyCode();

    const char*     getPriceAmountMicros();

    const char*     getSubscriptionPeriodUnitCode();

    const char*     getSubscriptionPeriod();

    const char*     getFreeTrialPeriod();

    const char*     getPromotionPrice();

    const char*     getPromotionPriceMicros();

    const char*     getPromotionUsePeriod();

    const char*     getPaymentGracePeriod();

    virtual void    dump();
};
}


#ifdef __cplusplus
}
#endif
