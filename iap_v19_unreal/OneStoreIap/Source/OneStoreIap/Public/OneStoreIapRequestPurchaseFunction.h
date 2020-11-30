// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/OnlineBlueprintCallProxyBase.h"
#include "OnlineSubsystem.h"
#include "OneStoreIapInterface.h"
#include "OneStoreIapCommonError.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif


#include "OneStoreIapRequestPurchaseFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOneStoreIapRequestPurchaseResult, const int32&, resultCode, const FOneStoreIapPurchaseData&, PurchaseData);


UCLASS(MinimalAPI)
class UOneStoreIapRequestPurchaseFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIapCommonError
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapRequestPurchaseResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapRequestPurchaseResult OnFailure;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapRequestPurchaseResult OnNeedUpdate;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapRequestPurchaseResult OnNeedLogin;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIapRequestPurchaseFunction* OneStoreIapRequestPurchase(UObject* WorldContextObject, const FString& ProductType, const FString& ProductId, const FString& ProductName, const FString& DevPayload);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	//void connect();

	// ¿ø½ºÅä¾î ÀÎ¾Û ÇÁ·Î´öÆ® ID ¿äÃ» ½ºÅÂÆ½ µ¨¸®°ÔÀÌÆ®
	//DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapProductDetails, bool, const TArray<FInAppPurchaseProductInfo>&);//
	//DECLARE_DELEGATE_OneParam(FStaticOneTest, bool);
	//static FStaticOneTest StaticOneStoreIapGetProductDetails;
	DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapRequestPurchase, int, const FOneStoreIapPurchaseData&);
	static FStaticOneStoreIapRequestPurchase StaticOneStoreIapRequestPurchase;

private:

	void OnCompleteRequestPurchase(int resultCode, const FOneStoreIapPurchaseData& purchaseDataAndSignature);

	// The world context object in which this call is taking place
	FString ProductType;
	FString ProductId;
	FString ProductName;
	FString DevPayload;

	UObject* WorldContextObject;
};

