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


#include "OneStoreIapProductDetailsFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOneStoreIapProductDetailsResult, const int32&, resultCode, const TArray<FOneStoreIapProductData>&, InAppProductInfo);

UCLASS(MinimalAPI)
class UOneStoreIapProductDetailsFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIapCommonError
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapProductDetailsResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapProductDetailsResult OnFailure;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapProductDetailsResult OnNeedUpdate;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapProductDetailsResult OnNeedLogin;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIapProductDetailsFunction* OneStoreIapGetProductDetails(UObject* WorldContextObject, const FString& ProductType, const TArray<FString>& ProductList);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	// ¿ø½ºÅä¾î ÀÎ¾Û ÇÁ·Î´öÆ® ID ¿äÃ» ½ºÅÂÆ½ µ¨¸®°ÔÀÌÆ®
	DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapProductDetails, int, const TArray<FOneStoreIapProductData>&);
	static FStaticOneStoreIapProductDetails StaticOneStoreIapGetProductDetails;

private:

	void OnCompleteGetProductDetails(int resultCode, const TArray<FOneStoreIapProductData>& ProductDetailList);

	// The world context object in which this call is taking place
	FString ProductType;
	TArray<FString> ProductList;

	UObject* WorldContextObject;
};

