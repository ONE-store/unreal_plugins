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


#include "OneStoreIapAcknowledgePurchaseFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOneStoreIapAcknowledgeResult, const int32&, resultCode, const FOneStoreIapPurchaseData&, OriginalPurchaseData);

//DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapProductDetails, bool, const TArray<FString>&);

UCLASS(MinimalAPI)
class UOneStoreIapAcknowledgePurchaseFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIapCommonError
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapAcknowledgeResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapAcknowledgeResult OnFailure;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapAcknowledgeResult OnNeedUpdate;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapAcknowledgeResult OnNeedLogin;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIapAcknowledgePurchaseFunction* OneStoreIapAcknowledgePurchase(UObject* WorldContextObject, const FString& PurchaseData, const FString& devPayload);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapAcknowledge, int, const FOneStoreIapPurchaseData&);
	static FStaticOneStoreIapAcknowledge StaticOneStoreIapAcknowledgePurchase;

private:

	void OnCompleteAcknowledge(int resultCode, const FOneStoreIapPurchaseData& OriginalPurchaseData);

	// The world context object in which this call is taking place
	FString PurchaseData;
	FString DevPayload;

	UObject* WorldContextObject;
};

