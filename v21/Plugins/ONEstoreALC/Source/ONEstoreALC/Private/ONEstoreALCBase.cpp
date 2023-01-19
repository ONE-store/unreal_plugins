/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */


#include "ONEstoreALCBase.h"
#include "ONEstoreALC.h"



#if PLATFORM_ANDROID
bool UONEstoreALCAsyncBase::m_setCallbackListener;
ONEstoreALCListener	UONEstoreALCAsyncBase::m_callbackListener;
#endif


//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------


void UONEstoreALCShowToast::showToast( FString str )
{	
#if PLATFORM_ANDROID
	ONESTORE_ALC::NativeAlcHelper->showToast(TCHAR_TO_UTF8(*str));
#endif
}


//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------


#if PLATFORM_ANDROID

void ONEstoreALCListener::onGranted( const char* license, const char* signature )
{
	int32_t nret = 0;
	FString fmsg( UTF8_TO_TCHAR( "success" ) );
	FString flicense( UTF8_TO_TCHAR( license ) );
	FString fsignature( UTF8_TO_TCHAR( signature ) );
	m_OnResultListener.ExecuteIfBound( nret, fmsg, flicense, fsignature );
}


void ONEstoreALCListener::onDenied()
{
	int32_t nret = 9999;
	FString fmsg( UTF8_TO_TCHAR( "denied" ) );
	FString femptyString( UTF8_TO_TCHAR( "" ) );
	m_OnResultListener.ExecuteIfBound( nret, fmsg, femptyString, femptyString );
}


void ONEstoreALCListener::onError( int code, const char* msg ) 
{
	FString fmsg( UTF8_TO_TCHAR( msg ) ); 
	FString femptyString( UTF8_TO_TCHAR( "" ) );
	m_OnResultListener.ExecuteIfBound( code, fmsg, femptyString, femptyString );
}


#endif


//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------


UONEstoreALCAsyncBase::UONEstoreALCAsyncBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if PLATFORM_ANDROID
	if (m_setCallbackListener == false) {
		m_setCallbackListener = true;
		ONESTORE_ALC::NativeAlcHelper->changeCallbacksListener(getListener());
	}
#endif
}


#if PLATFORM_ANDROID
ONEstoreALCListener* UONEstoreALCAsyncBase::getListener() {
	return &m_callbackListener;
}
#endif



//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
