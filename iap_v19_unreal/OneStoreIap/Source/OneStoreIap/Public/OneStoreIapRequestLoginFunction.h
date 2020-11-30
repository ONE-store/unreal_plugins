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


#include "OneStoreIapRequestLoginFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneStoreIapRequestLoginResult, const int32&, resultCode);

UCLASS(MinimalAPI)
class UOneStoreIapRequestLoginFunction : public UOnlineBlueprintCallProxyBase, public OneStoreIapCommonError
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapRequestLoginResult OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FOneStoreIapRequestLoginResult OnFailure;


	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OneStore")
	static UOneStoreIapRequestLoginFunction* OneStoreIapRequestLogin(UObject* WorldContextObject);

	virtual void Activate() override;

	static void HandleError(int errorCode);

public :

	DECLARE_DELEGATE_OneParam(FStaticOneStoreIapRequestLogin, int);
	static FStaticOneStoreIapRequestLogin StaticOneStoreIapRequestLogin;

private:

	void OnCompleteRequestLogin(int resultCode);

	UObject* WorldContextObject;
};

