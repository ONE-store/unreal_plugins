// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/OnlineBlueprintCallProxyBase.h"
#include "OnlineSubsystem.h"
#include "OneStoreIapInterface.h"
#include "OneStoreIapCommonError.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#endif

#include "OneStoreIapConsumePurchaseFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOneStoreIapConsumeResult, const int32&, resultCode, const FOneStoreIapPurchaseData&, OriginalPurchaseData);


UCLASS(MinimalAPI)
class UOneStoreIapConsumePurchaseFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIapCommonError
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapConsumeResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapConsumeResult OnFailure;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapConsumeResult OnNeedUpdate;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapConsumeResult OnNeedLogin;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIapConsumePurchaseFunction* OneStoreIapConsumePurchase(UObject* WorldContextObject, const FString& PurchaseData, const FString& devPayload);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapConsume, int, const FOneStoreIapPurchaseData&);
	static FStaticOneStoreIapConsume StaticOneStoreIapConsumePurchase;

private:

	void OnCompleteConsume(int resultCode, const FOneStoreIapPurchaseData& OriginalPurchaseData);

	// The world context object in which this call is taking place
	FString PurchaseData;
	FString DevPayload;

	UObject* WorldContextObject;
};

