/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#include "ONEstoreIapObject.h"
#include <jni.h>
#include <list>
#include <string>


#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP {

enum class ProductType;

class ProductDetail : public IapObject {
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

    static std::unique_ptr<ProductDetail> getProductDetail( jobject obj );
    static std::unique_ptr<std::list<ProductDetail>> getProductDetailsList( jobject obj );
    static std::unique_ptr<jobject> getProductDetailsListObj( const char* params, va_list args );
    static std::unique_ptr<jobject> getProductDetailsListObj( std::list<std::string>* plist );

protected:
    std::string OrigJson;
    std::string ProductId;
    std::string Title;
    std::string Price;
    std::string PriceAmountMicros;
    std::string PriceCurrencyCode;
    std::string SubscriptionPeriod;
    std::string SubscriptionPeriodUnitCode;
    std::string FreeTrialPeriod;
    std::string PromotionPrice;
    std::string PromotionPriceMicros;
    std::string PromotionUsePeriod;
    std::string PaymentGracePeriod;

    ProductType productType;
};
}


#ifdef __cplusplus
}
#endif
