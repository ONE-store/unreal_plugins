/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#if PLATFORM_ANDROID
#include "../ONEstoreNativeAlcHelper/include/ONEstoreAlcEngine.h"
#endif

#include "ONEstoreALCBase.generated.h"


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// show toast.

UCLASS(MinimalAPI)
class UONEstoreALCShowToast : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "ONEstore|ALC",
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



DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnResult, const int32&, code, const FString&, msg,
											  const FString&, license, const FString&, signature);

#if PLATFORM_ANDROID
class ONEstoreALCListener : public ONESTORE_ALC::CallbacksListener{
public:
	ONEstoreALCListener() {};
	virtual ~ONEstoreALCListener() {};

public: 
	//-------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------
	// onestore nativeiaphelper callback listener
	virtual void onGranted( const char* license, const char* signature ) override;
	virtual void onDenied() override;
	virtual void onError( int code, const char* msg ) override;

public:
	DECLARE_DELEGATE_FourParams(FDEL_Result, const int32&, const FString&, const FString&, const FString& );
	FDEL_Result	 m_OnResultListener;
};

#endif


UCLASS(abstract)
class UONEstoreALCAsyncBase : public UBlueprintAsyncActionBase
{
public:
	GENERATED_UCLASS_BODY()
		
protected:
	const UObject*				m_pWorld;
	FString						m_publicKey;
	

#if PLATFORM_ANDROID
public:
	ONEstoreALCListener*		getListener();	

private:
	static bool					m_setCallbackListener;
	static ONEstoreALCListener	m_callbackListener;
#endif
};
