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

#include "OneStoreIapManageRecurringFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOneStoreIapManageRecurringResult, const int32&, resultCode, const FString&, Action, const FOneStoreIapPurchaseData&, OriginalPurchaseData);

UCLASS(MinimalAPI)
class UOneStoreIapManageRecurringFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIapCommonError
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapManageRecurringResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapManageRecurringResult OnFailure;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapManageRecurringResult OnNeedUpdate;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapManageRecurringResult OnNeedLogin;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIapManageRecurringFunction* OneStoreIapManageRecurring(UObject* WorldContextObject, const FString& PurchaseData);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	DECLARE_DELEGATE_ThreeParams(FStaticOneStoreIapManageRecurring, int, const FString&, const FOneStoreIapPurchaseData&);
	static FStaticOneStoreIapManageRecurring StaticOneStoreIapManageRecurring;

private:

	void OnCompleteManageRecurring(int resultCode, const FString& Action, const FOneStoreIapPurchaseData& OriginalPurchaseData);

	// The world context object in which this call is taking place
	FString PurchaseData;

	UObject* WorldContextObject;
};

