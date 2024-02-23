/*
 * Do Not Modify This File.
 * Copyright @ 2022, ONEstore. All rights reserved.
 */

#include "ONEstoreIAPIsFeatureSupported.h"
#include "ONEstoreIAP.h"

UONEstoreIAPIsFeatureSupported::UONEstoreIAPIsFeatureSupported(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}


FONEstoreIapResult UONEstoreIAPIsFeatureSupported::IsFeatureSupported( const FString feature )
{	
#if PLATFORM_ANDROID
	say("d. check in");	
	std::unique_ptr<IapResult> p = NativeIapHelper->isFeatureSupported(TCHAR_TO_UTF8(*feature));
	
	FONEstoreIapResult result( p.get() );
	return result;
#else
	FONEstoreIapResult result;
	return result;
#endif
}