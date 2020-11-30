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


#include "OneStoreIapGetStoreCodeFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOneStoreCodeResult, const int32&, resultCode, const FString&, StoreCode);

UCLASS(MinimalAPI)
class UOneStoreIapGetStoreCodeFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIapCommonError
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FOneStoreCodeResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreCodeResult OnFailure;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreCodeResult OnNeedUpdate;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreCodeResult OnNeedLogin;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIapGetStoreCodeFunction* OneStoreIapGetStoreCode(UObject* WorldContextObject);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	// ¿ø½ºÅä¾î ÀÎ¾Û ÇÁ·Î´öÆ® ID ¿äÃ» ½ºÅÂÆ½ µ¨¸®°ÔÀÌÆ®
	DECLARE_DELEGATE_TwoParams(FStaticOneStoreIapStoreCode, int, const FString&);
	static FStaticOneStoreIapStoreCode StaticOneStoreIapGetStoreCode;

private:

	void OnCompleteGetStoreCode(int resultCode, const FString& StoreCode);

	UObject* WorldContextObject;
};

