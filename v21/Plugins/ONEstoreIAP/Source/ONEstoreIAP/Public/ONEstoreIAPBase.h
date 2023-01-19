/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#if PLATFORM_ANDROID
#include "../ONEstoreNativeIapHelper/include/ONEstoreIapEngine.h"
using namespace ONESTORE_IAP;
#endif

#include "ONEstoreIAPBase.generated.h"


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// ONEstore Enum Classes.

UENUM(BlueprintType)
enum class EONEstoreConnectionState : uint8 {
	DISCONNECTED = 0,
	CONNECTING,
	CONNECTED,
	CLOSED
};


UENUM(BlueprintType)
enum class EONEstoreFeatureType : uint8 {
	SUBSCRIPTIONS = 0,          // "subscriptions";
	SUBSCRIPTIONS_UPDATE,       // "subscriptionsUpdate";
	PRICE_CHANGE_CONFIRMATION   // "priceChangeConfirmation";
};


UENUM(BlueprintType)
enum class EONEstorePurchaseState : uint8 {
	PURCHASED = 0,
	CANCEL,
	REFUND
};


UENUM(BlueprintType)
enum class EONEstoreAcknowledgeState : uint8 {
	NOT_ACKNOWLEDGED = 0,
	ACKNOWLEDGED
};


UENUM(BlueprintType)
enum class EONEstoreRecurringState : uint8 {
	RECURRING = 0,
	CANCEL
};


UENUM(BlueprintType)
enum class EONEstoreProductType : uint8 {
	INAPP = 0,
	AUTO,
	SUBS,
	ALL
};



UENUM(BlueprintType)
enum class EONEstoreProrationMode : uint8 {
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



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// ONEstore Structure.

USTRUCT(BlueprintType)
struct FONEstoreIapResult
{
public:
	GENERATED_USTRUCT_BODY()

	FONEstoreIapResult()
	: code(0), message() {
	}


#if PLATFORM_ANDROID
	FONEstoreIapResult(std::unique_ptr<IapResult>& result) {
		code = (int32)result->getResponseCode();
		message = UTF8_TO_TCHAR(result->getMessage());
	}
#endif

	UPROPERTY(BlueprintReadOnly)
	int32 code;
	UPROPERTY(BlueprintReadOnly)
	FString message;
};


USTRUCT(BlueprintType)
struct FONEstoreProductDetail
{
	GENERATED_USTRUCT_BODY()

	FONEstoreProductDetail() {
	};

#if PLATFORM_ANDROID
	FONEstoreProductDetail(ProductDetail* p) {
		OriginalJson = FString(UTF8_TO_TCHAR(p->getOriginalJson()));
		ProductId = FString(UTF8_TO_TCHAR(p->getProductId()));
		Title = FString(UTF8_TO_TCHAR(p->getTitle()));
		Price = FString(UTF8_TO_TCHAR(p->getPrice()));
		PriceAmountMicros = FString(UTF8_TO_TCHAR(p->getPriceAmountMicros()));
		PriceCurrencyCode = FString(UTF8_TO_TCHAR(p->getPriceCurrencyCode()));
		SubscriptionPeriodUnitCode = FString(UTF8_TO_TCHAR(p->getSubscriptionPeriodUnitCode()));
		SubscriptionPeriod = FString(UTF8_TO_TCHAR(p->getSubscriptionPeriod()));
		FreeTrialPeriod = FString(UTF8_TO_TCHAR(p->getFreeTrialPeriod()));
		PromotionPrice = p->getPromotionPrice();
		PromotionPriceMicros = p->getPromotionPriceMicros();
		PromotionUsePeriod = p->getPromotionUsePeriod();
		PaymentGracePeriod = p->getPaymentGracePeriod();
		Type = (EONEstoreProductType)p->getType();
	}
#endif

	UPROPERTY(BlueprintReadOnly)
	FString OriginalJson;
	UPROPERTY(BlueprintReadOnly)
	FString ProductId;
	UPROPERTY(BlueprintReadOnly)
	FString Title;
	UPROPERTY(BlueprintReadOnly)
	FString Price;
	UPROPERTY(BlueprintReadOnly)
	FString PriceAmountMicros;
	UPROPERTY(BlueprintReadOnly)
	FString PriceCurrencyCode;
	UPROPERTY(BlueprintReadOnly)
	FString SubscriptionPeriod;
	UPROPERTY(BlueprintReadOnly)
	FString SubscriptionPeriodUnitCode;
	UPROPERTY(BlueprintReadOnly)
	FString FreeTrialPeriod;
	UPROPERTY(BlueprintReadOnly)
	FString PromotionPrice;
	UPROPERTY(BlueprintReadOnly)
	FString PromotionPriceMicros;
	UPROPERTY(BlueprintReadOnly)
	FString PromotionUsePeriod;
	UPROPERTY(BlueprintReadOnly)
	FString PaymentGracePeriod;
	UPROPERTY(BlueprintReadOnly)
	EONEstoreProductType Type;
};


USTRUCT(BlueprintType)
struct FONEstorePurchaseData
{
	GENERATED_USTRUCT_BODY()
		
	FONEstorePurchaseData(){
	};

#if PLATFORM_ANDROID
	FONEstorePurchaseData(PurchaseData* p) {
		if (p == nullptr)
			return;

		OriginalJson = FString(UTF8_TO_TCHAR(p->getOriginalJson()));
		OrderId = FString(UTF8_TO_TCHAR(p->getOrderId())); 
		PackageName = FString(UTF8_TO_TCHAR(p->getPackageName())); 
		ProductId = FString(UTF8_TO_TCHAR(p->getProductId())); 
		PurchaseTime = p->getPurchaseTime(); 
		IsAcknowledged = p->isAcknowledged();
		DeveloperPayload = FString(UTF8_TO_TCHAR(p->getDeveloperPayload()));		
		PurchaseId = FString(UTF8_TO_TCHAR(p->getPurchaseId()));
		PurchaseToken = FString(UTF8_TO_TCHAR(p->getPurchaseToken()));		
		BillingKey = FString(UTF8_TO_TCHAR(p->getBillingKey()));
		purchaseState = (EONEstorePurchaseState)p->getPurchaseState(); 
		recurringState = (EONEstoreRecurringState)p->getRecurringState();
		Quantity = p->getQuantity();
		Signature = FString(UTF8_TO_TCHAR(p->getSignature()));
	}
#endif
	
	UPROPERTY(BlueprintReadOnly)
	FString OriginalJson;	
	UPROPERTY(BlueprintReadOnly)
	FString OrderId;
	UPROPERTY(BlueprintReadOnly)
	FString PackageName;
	UPROPERTY(BlueprintReadOnly)
	FString ProductId;
	UPROPERTY(BlueprintReadOnly)
	FString DeveloperPayload; 		
	UPROPERTY(BlueprintReadOnly)
	FString PurchaseId;	
	UPROPERTY(BlueprintReadOnly)
	FString PurchaseToken;
	UPROPERTY(BlueprintReadOnly)
	FString BillingKey;	
	UPROPERTY(BlueprintReadOnly)
	FString Signature;
	UPROPERTY(BlueprintReadOnly)
	bool	IsAcknowledged;
	UPROPERTY(BlueprintReadOnly)
	int32	Quantity;
	UPROPERTY(BlueprintReadOnly)
	int64	PurchaseTime;
	UPROPERTY(BlueprintReadOnly)
	EONEstorePurchaseState purchaseState;		
	UPROPERTY(BlueprintReadOnly)
	EONEstoreRecurringState recurringState;

};




#if PLATFORM_ANDROID
class UNREAL_TO_ONESTORE_PRODUCTDETAIL : public ProductDetail{
public:
	UNREAL_TO_ONESTORE_PRODUCTDETAIL( const FONEstoreProductDetail* p) {
		OrigJson = TCHAR_TO_UTF8(*(p->OriginalJson));
		ProductId = TCHAR_TO_UTF8(*(p->ProductId));
		Title = TCHAR_TO_UTF8(*(p->Title));
		Price = TCHAR_TO_UTF8(*(p->Price));
		PriceAmountMicros = TCHAR_TO_UTF8(*(p->PriceAmountMicros));
		PriceCurrencyCode = TCHAR_TO_UTF8(*(p->PriceCurrencyCode));
		SubscriptionPeriod = TCHAR_TO_UTF8(*(p->SubscriptionPeriod));
		SubscriptionPeriodUnitCode = TCHAR_TO_UTF8(*(p->SubscriptionPeriodUnitCode));
		FreeTrialPeriod = TCHAR_TO_UTF8(*(p->FreeTrialPeriod));
		PromotionPrice = TCHAR_TO_UTF8(*(p->PromotionPrice));
		PromotionPriceMicros = TCHAR_TO_UTF8(*(p->PromotionPriceMicros));
		PromotionUsePeriod = TCHAR_TO_UTF8(*(p->PromotionUsePeriod));
		PaymentGracePeriod = TCHAR_TO_UTF8(*(p->PaymentGracePeriod));
		productType = (ProductType)p->Type;
	};

	virtual ~UNREAL_TO_ONESTORE_PRODUCTDETAIL(){};

	ProductDetail* get() {
		return (ProductDetail*)this;
	}
	
};


class UNREAL_TO_ONESTORE_PURCHASEDATA : public PurchaseData {
public:
	UNREAL_TO_ONESTORE_PURCHASEDATA(const FONEstorePurchaseData& p) {
		OrigJson = TCHAR_TO_UTF8(*(p.OriginalJson));
		BillingKey = TCHAR_TO_UTF8(*(p.BillingKey));
		DeveloperPayload = TCHAR_TO_UTF8(*(p.DeveloperPayload));
		OrderId = TCHAR_TO_UTF8(*(p.OrderId));
		PackageName = TCHAR_TO_UTF8(*(p.PackageName));
		ProductId = TCHAR_TO_UTF8(*(p.ProductId));
		PurchaseId = TCHAR_TO_UTF8(*(p.PurchaseId));
		PurchaseToken = TCHAR_TO_UTF8(*(p.PurchaseToken));
		Signature = TCHAR_TO_UTF8(*(p.Signature));
		IsAcknowledged = p.IsAcknowledged;
		PurchaseTime = p.PurchaseTime;
		Quantity = p.Quantity;
		purchaseState = (PurchaseState)p.purchaseState;
		recurringState = (RecurringState)p.recurringState;
	};

	virtual ~UNREAL_TO_ONESTORE_PURCHASEDATA() {};

	PurchaseData* get() {
		return (PurchaseData*)this;
	}
};
#endif



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// show toast.

UCLASS(MinimalAPI)
class UONEstoreIAPShowToast : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "ONEstore|IAP",
		meta = (DisplayName = "ShowToast", WorldContext = "WorldContext"))
	static void showToast(FString str);
};


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// ONEstore Delegate Defines
// basic. startconnection & launchloginflowasync
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIapResult, const int32&, code, const FString&, msg);
// consume & acknowledge
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPurchaseData, const int32&, code, const FString&, msg, const FONEstorePurchaseData&, data);
// querypurchaseasync
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPurchaseDataList, const int32&, code, const FString&, msg, const TArray<FONEstorePurchaseData>&, list);
// launchpurchaseflow & queryproductdetatilsasync
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnProductDetailList, const int32&, code, const FString&, msg, const TArray<FONEstoreProductDetail>&, list);
// storeinfo
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStoreInfo, const int32&, code, const FString&, msg, const FString&, info);
// managerecurringproductasync
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRecurringState, const int32&, code, const FString&, msg, const FONEstorePurchaseData&, data, const EONEstoreRecurringState&, state);


#if PLATFORM_ANDROID
class ONEstoreIAPListener : public ONESTORE_IAP::CallbacksListener{
public:
	ONEstoreIAPListener() {};
	virtual ~ONEstoreIAPListener() {};

public: 
	//-------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------
	// onestore nativeiaphelper callback listener	
	virtual void onSetupFinished(IapResult* pResult) override;
	virtual void onServiceDisconnected() override;

	virtual void onPurchasesUpdated(IapResult* prepResultsult, std::list<PurchaseData> *plist) override;
	virtual void onQueryPurchasesAsync(IapResult* pResult, std::list<PurchaseData>* plist) override;	
	virtual void onQueryProductDetailsAsync(IapResult* pResult, std::list<ProductDetail>* plist) override;
	virtual void onAcknowledgeAsync(IapResult* pResult, PurchaseData* pdata) override;
	virtual void onConsumeAsync(IapResult* pResult, PurchaseData* pdata) override;
	
	virtual void onLaunchLoginFlowAsync(IapResult* pResult) override;
	virtual void onLaunchUpdateOrInstallFlow(IapResult* pResult) override;
	
	virtual void onManageRecurringProductAsync(IapResult* pResult, PurchaseData* pdata, enum RecurringState state) override;
	virtual void onStoreInfoAsync(IapResult* pResult, const char* pinfo) override;

public:
	// members
	DECLARE_DELEGATE_TwoParams(FDEL_IapResult, const int32&, const FString&);
	FDEL_IapResult			m_OnIapResultListener; 
	DECLARE_DELEGATE_ThreeParams(FDEL_PurchaseData, const int32&, const FString&, const FONEstorePurchaseData&);
	FDEL_PurchaseData		m_OnPurchaseDataListener;	
	DECLARE_DELEGATE_ThreeParams(FDEL_PurchaseDataList, const int32&, const FString&, const TArray<FONEstorePurchaseData>&);
	FDEL_PurchaseDataList	m_OnPurchaseDataListListener;	
	DECLARE_DELEGATE_ThreeParams(FDEL_ProductDetilList, const int32&, const FString&, const TArray<FONEstoreProductDetail>&);
	FDEL_ProductDetilList	m_OnProductDetailListListener;	
	DECLARE_DELEGATE_ThreeParams(FDEL_StoreInfo, const int32&, const FString&, const FString&);
	FDEL_StoreInfo			m_OnStoreInfoListener;	
	DECLARE_DELEGATE_FourParams(FDEL_RecurringState, const int32&, const FString&, const FONEstorePurchaseData&, const EONEstoreRecurringState&);
	FDEL_RecurringState		m_OnRecurringStateListener;	

private:
	void		processIapResult(IapResult*);
	void		processPurchaseDataResult(IapResult*, PurchaseData*);
	void		processPurchaseDataListResult(IapResult*, std::list<PurchaseData> *);
};

#endif

UCLASS(abstract)
class UONEstoreIAPSyncBase : public UBlueprintFunctionLibrary
{
public:
	GENERATED_UCLASS_BODY()
};


UCLASS(abstract)
class UONEstoreIAPAsyncBase : public UBlueprintAsyncActionBase
{
public:
	GENERATED_UCLASS_BODY()

protected:
	const UObject*				m_pWorld;

#if PLATFORM_ANDROID
public:
	ONEstoreIAPListener*		getListener();

private:
	static bool					m_setCallbackListener;
	static ONEstoreIAPListener	m_callbackListener;
#endif
};
