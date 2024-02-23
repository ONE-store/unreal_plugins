/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */


#include "ONEstoreALCStrictQueryLicenseAsync.h"
#include "ONEstoreALC.h"


UONEstoreALCStrictQueryLicenseAsync::UONEstoreALCStrictQueryLicenseAsync( 
	const FObjectInitializer& ObjectInitializer )
: Super( ObjectInitializer )
{
}


UONEstoreALCStrictQueryLicenseAsync* UONEstoreALCStrictQueryLicenseAsync::StrictQueryLicenseAsync(
	const UObject* pWorld, const FString& publicKey )
{
	UONEstoreALCStrictQueryLicenseAsync* pthis = 
		NewObject<UONEstoreALCStrictQueryLicenseAsync>();
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


void UONEstoreALCStrictQueryLicenseAsync::OnCompleted( const int32& code,
													   const FString& msg,
													   const FString& license,
													   const FString& signature )
{
#if PLATFORM_ANDROID	
	switch ((ONESTORE_ALC::ResponseCode)code) {
	case ONESTORE_ALC::ResponseCode::RESULT_OK:
		OnGranted.Broadcast(code, msg, license, signature); break;
	case ONESTORE_ALC::ResponseCode::RESULT_DENIED:
		OnDenied.Broadcast(code, msg, license, signature); break;
	case ONESTORE_ALC::ResponseCode::RESULT_NEED_LOGIN:
		OnNeedLogin.Broadcast(code, msg, license, signature); break;
	case ONESTORE_ALC::ResponseCode::RESULT_NEED_UPDATE:
		OnNeedUpdate.Broadcast(code, msg, license, signature); break;
	default:
		OnError.Broadcast(code, msg, license, signature); break;
	}
#endif 
}
