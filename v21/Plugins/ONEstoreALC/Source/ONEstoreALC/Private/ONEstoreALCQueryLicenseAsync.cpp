/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */


#include "ONEstoreALCQueryLicenseAsync.h"
#include "ONEstoreALC.h"


UONEstoreALCQueryLicenseAsync::UONEstoreALCQueryLicenseAsync(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


UONEstoreALCQueryLicenseAsync* UONEstoreALCQueryLicenseAsync::QueryLicenseAsync(
	const UObject* pWorld, const FString& publicKey)
{
	UONEstoreALCQueryLicenseAsync* pthis = NewObject<UONEstoreALCQueryLicenseAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_publicKey = publicKey;

	return pthis;
}


void UONEstoreALCQueryLicenseAsync::Activate()
{
#if PLATFORM_ANDROID
	getListener()->m_OnResultListener.BindUObject(
		this, &UONEstoreALCQueryLicenseAsync::OnCompleted );

	ONESTORE_ALC::NativeAlcHelper->queryLicense( TCHAR_TO_UTF8( *m_publicKey) );
#endif 
}



void UONEstoreALCQueryLicenseAsync::OnCompleted(const int32& code,
												const FString& msg,
												const FString& license,
												const FString& signature)
{
#if PLATFORM_ANDROID
	switch (code) {
	case 0:
		OnGranted.Broadcast(code, msg, license, signature); break;
	case 9999:
		OnDenied.Broadcast(code, msg, license, signature); break;
	case 10:
		OnNeedLogin.Broadcast(code, msg, license, signature); break;
	case 11:
		OnNeedUpdate.Broadcast(code, msg, license, signature); break;
	default:
		OnError.Broadcast(code, msg, license, signature); break;
	}
#endif 
}




