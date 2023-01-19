/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */


#include "ONEstoreALCStrictQueryLicenseAsync.h"
#include "ONEstoreALC.h"


UONEstoreALCStrictQueryLicenseAsync::UONEstoreALCStrictQueryLicenseAsync( const FObjectInitializer& ObjectInitializer )
: Super( ObjectInitializer )
{
}


UONEstoreALCStrictQueryLicenseAsync* UONEstoreALCStrictQueryLicenseAsync::StrictQueryLicenseAsync(
	const UObject* pWorld, const FString& publicKey )
{
	UONEstoreALCStrictQueryLicenseAsync* pthis = NewObject<UONEstoreALCStrictQueryLicenseAsync>();
	pthis->m_pWorld = pWorld;
	pthis->m_publicKey = publicKey;
	return pthis;
}


void UONEstoreALCStrictQueryLicenseAsync::Activate()
{
#if PLATFORM_ANDROID
	getListener()->m_OnResultListener.BindUObject(
		this, &UONEstoreALCStrictQueryLicenseAsync::OnCompleted );

	ONESTORE_ALC::NativeAlcHelper->strictQueryLicense( TCHAR_TO_UTF8( *m_publicKey ) );
#endif 
}


void UONEstoreALCStrictQueryLicenseAsync::OnCompleted(const int32& code,
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
