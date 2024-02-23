/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#if PLATFORM_ANDROID
#include "../ONEstoreNativeIapHelper/include/ONEstoreIapEngine.h"
#include "../ONEstoreNativeIapHelper/include/ONEstoreIapSay.h"
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
	//FONEstoreIapResult( std::unique_ptr<IapResult> result ){
	FONEstoreIapResult(IapResult* pResult){
		code = (int32)pResult->getResponseCode();
		message = UTF8_TO_TCHAR(pResult->getMessage());
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


#if PLATFORM_ANDROID
	void dump() const{
		say2("ProductDetail ======================================================================");
		say2("OriginalJson : %s", TCHAR_TO_UTF8(*OriginalJson));
		say2("ProductId : %s", TCHAR_TO_UTF8(*ProductId));
		say2("Title : %s", TCHAR_TO_UTF8(*Title));
		say2("Type : %s",
			Type == EONEstoreProductType::INAPP ? "inapp" :
			Type == EONEstoreProductType::AUTO ? "auto" :
			Type == EONEstoreProductType::SUBS ? "subs" : "all");
		say2("Price : %s", TCHAR_TO_UTF8(*Price));
		say2("PriceAmountMicros : %s", TCHAR_TO_UTF8(*PriceAmountMicros));
		say2("PriceCurrencyCode : %s", TCHAR_TO_UTF8(*PriceCurrencyCode));
		say2("SubscriptionPeriodUnitCode : %s", TCHAR_TO_UTF8(*SubscriptionPeriodUnitCode));
		say2("SubscriptionPeriod : %s", TCHAR_TO_UTF8(*SubscriptionPeriod));
		say2("FreeTrialPeriod : %s", TCHAR_TO_UTF8(*FreeTrialPeriod));
		say2("PromotionPrice : %s", TCHAR_TO_UTF8(*PromotionPrice));
		say2("PromotionPriceMicros : %s", TCHAR_TO_UTF8(*PromotionPriceMicros));
		say2("PromotionUsePeriod : %s", TCHAR_TO_UTF8(*PromotionUsePeriod));
		say2("PaymentGracePeriod : %s", TCHAR_TO_UTF8(*PaymentGracePeriod));
		say2("ProductDetail end ===================================================================");
	}
#endif
};


USTRUCT(BlueprintType)
struct FONEstorePurchaseData
{
	GENERATED_USTRUCT_BODY()
		
	FONEstorePurchaseData(){
	};


#if PLATFORM_ANDROID
	FONEstorePurchaseData(PurchaseData* p) {		
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
	
	

#if PLATFORM_ANDROID
	void dump() const{
#if (UE_BUILD_SHIPPING != 0) 
		say2("FONEstorePurchaseData PurchaseData ======================================================================");
		say2("OriginalJson : %s", TCHAR_TO_UTF8(*OriginalJson));
		say2("OrderId : %s", TCHAR_TO_UTF8(*OrderId));
		say2("PackageName : %s", TCHAR_TO_UTF8(*PackageName));
		say2("ProductId : %s", TCHAR_TO_UTF8(*ProductId));
		say2("PurchaseTime : %lld", PurchaseTime); 
		say2("isAcknowledged : %s", IsAcknowledged ? "true" : "false");
		say2("DeveloperPayload : %s", TCHAR_TO_UTF8(*DeveloperPayload));
		say2("PurchaseId : %s", TCHAR_TO_UTF8(*PurchaseId));
		say2("PurchaseToken : %s", TCHAR_TO_UTF8(*PurchaseToken));
		say2("BillingKey : %s", TCHAR_TO_UTF8(*BillingKey));
		say2("PurchaseState : %s", 
			purchaseState == EONEstorePurchaseState::PURCHASED ? "PURCHASED" :
			purchaseState == EONEstorePurchaseState::CANCEL ? "CANCEL" :
			purchaseState == EONEstorePurchaseState::REFUND ? "REFUND" : "UNSPECIFIED_STATE" );
		say2("RecurringState : %s",
			recurringState == EONEstoreRecurringState::RECURRING ? "RECURRING" :
			recurringState == EONEstoreRecurringState::CANCEL ? "CANCEL" : "NON_AUTO_PRODUCT");

		say2("Quantity : %d", Quantity);
		say2("Signature : %s", TCHAR_TO_UTF8(*Signature));
		say2("FONEstorePurchaseData PurchaseData end ===================================================================");
#endif

	};
#endif
};





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
// Sync && Async 로 나눠서 super class 필요

// onestore iap client sync & async 함수 분류
// sync.
	// endConnection, isReady, getConnectionState, isFeatureSupported, verify
// async
	// startConnection, consume, acknowledge, getStoreInfo, launchXXX, manageRecurring, queryXXX
// no response 
	// endConnection, launchManageSubscription, 


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
	virtual void onPurchasesResponse(IapResult* pResult, std::list<PurchaseData>* plist) override;
	virtual void onPurchasesUpdated(IapResult* prepResultsult, std::list<PurchaseData> *plist) override;
	virtual void onProductDetailsResponse(IapResult* pResult, std::list<ProductDetail>* plist) override;
	virtual void onAcknowledgeResponse(IapResult* pResult, PurchaseData* pdata) override;
	virtual void onConsumeResponse(IapResult* pResult, PurchaseData* pdata) override;
	virtual void onLaunchLoginFlowResponse(IapResult* pResult) override;
	virtual void onLaunchUpdateOrInstallFlowResponse(IapResult* pResult) override;
	virtual void onRecurringResponse(IapResult* pResult, PurchaseData* pdata, enum RecurringState state) override;
	virtual void onStoreInfoResponse(IapResult* pResult, const char* pinfo) override;
	

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
