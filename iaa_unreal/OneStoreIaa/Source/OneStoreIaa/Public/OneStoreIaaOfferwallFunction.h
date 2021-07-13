// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/OnlineBlueprintCallProxyBase.h"
#include "OneStoreIaaInterface.h"
#include "OneStoreIaaCommon.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif


#include "OneStoreIaaOfferwallFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneStoreIaaOfferwallResult, const int32&, resultCode);

UCLASS(MinimalAPI)
class UOneStoreIaaOfferwallFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIaaCommon
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
		FOneStoreIaaOfferwallResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
		FOneStoreIaaOfferwallResult OnFailure;


	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIaaOfferwallFunction* OneStoreIaaOfferwall(UObject* WorldContextObject);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	DECLARE_DELEGATE_OneParam(FStaticOneStoreIaaOfferwall, int);
	static FStaticOneStoreIaaOfferwall StaticOneStoreIaaOfferwall;

private:

	void OnCompleteOfferwall(int resultCode);

	UObject* WorldContextObject;
};

