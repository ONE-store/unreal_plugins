/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPGetStoreInfoAsync.h"
#include "ONEstoreIAP.h"
#include "ONEstoreIAPBase.h"

UONEstoreIAPGetStoreInfoAsync::UONEstoreIAPGetStoreInfoAsync(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


UONEstoreIAPGetStoreInfoAsync* UONEstoreIAPGetStoreInfoAsync::GetStoreInfo(const UObject* pWorld)
{	
	UONEstoreIAPGetStoreInfoAsync* pthis = 
		NewObject<UONEstoreIAPGetStoreInfoAsync>();
	pthis->m_pWorld = pWorld;

#if PLATFORM_ANDROID
	say("d. check in");
#endif

	return pthis;
}


void UONEstoreIAPGetStoreInfoAsync::Activate()
{
#if PLATFORM_ANDROID
	say("d. check in");
	getListener()->m_OnStoreInfoListener.BindUObject(
		this, &UONEstoreIAPGetStoreInfoAsync::OnCompleted);

	NativeIapHelper->getStoreInfoAsync();
#endif 
}



void UONEstoreIAPGetStoreInfoAsync::OnCompleted( const int32& code, 
												const FString& message,
												const FString& info )
{
#if PLATFORM_ANDROID
	say("d. check in");
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT	
	say("d. result( %d, %s ), info( %s )", code, TCHAR_TO_UTF8(*message), TCHAR_TO_UTF8(*info));
#endif

	switch ((ResponseCode)code) {
	case ResponseCode::RESULT_OK:
		OnSuccess.Broadcast(code, message, info);	break;
	case ResponseCode::RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(code, message, info); break;
	case ResponseCode::RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(code, message, info); break;
	default:
		OnFailure.Broadcast(code, message, info); break;
	}
#endif
}

