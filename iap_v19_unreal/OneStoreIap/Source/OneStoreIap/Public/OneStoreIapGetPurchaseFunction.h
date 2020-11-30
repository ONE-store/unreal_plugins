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


#include "OneStoreIapGetPurchaseFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOneStoreIapPurchaseResult, const int32&, resultCode, const TArray<FOneStoreIapPurchaseData>&, OneStoreIapPurchaseData);

UCLASS(MinimalAPI)
class UOneStoreIapGetPurchaseFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIapCommonError
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapPurchaseResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapPurchaseResult OnFailure;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapPurchaseResult OnNeedUpdate;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapPurchaseResult OnNeedLogin;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIapGetPurchaseFunction* OneStoreIapPurchaseInfo(UObject* WorldContextObject, const FString& ProductType);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	//void connect();

	// ¿ø½ºÅä¾î ÀÎ¾Û ÇÁ·Î´öÆ® ID ¿äÃ» ½ºÅÂÆ½ µ¨¸®°ÔÀÌÆ®
	//DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapProductDetails, bool, const TArray<FInAppPurchaseProductInfo>&);//
	//DECLARE_DELEGATE_OneParam(FStaticOneTest, bool);
	//static FStaticOneTest StaticOneStoreIapGetProductDetails;
	DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapPurchase, int, const TArray<FOneStoreIapPurchaseData>&);
	static FStaticOneStoreIapPurchase StaticOneStoreIapGetPurchaseInfo;

private:

	void OnCompleteGetPurchase(int resultCode, const TArray<FOneStoreIapPurchaseData>& OneStoreIapPurchaseData);

	// The world context object in which this call is taking place
	FString ProductType;

	UObject* WorldContextObject;
};

